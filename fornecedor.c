#include "cJson.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "fornecedor.h"
#include "financas.h"
#include "estoque.h"

#define CAMINHO "arquivo.json"

void pedeFornecedor(char *nomeJogo)
{
    // ========= Tratamento do arquivo =========

    // Realiza a abertura do arquivo
    FILE *arquivo = abreArq(CAMINHO, "r");

    // Pega o tamanho do arquivo indo com o ponteiro ate o final usando seek
    fseek(arquivo, 0, SEEK_END);
    long tamanhoArquivo = ftell(arquivo);
    // Volta o ponteiro para o inicio do arquivo
    fseek(arquivo, 0, SEEK_SET);

    // Realiza um malloc para conteudoArquivo, onde vai ser salvo o arquivo todo json
    char *conteudoArquivo = (char *)malloc(tamanhoArquivo + 1);
    // Faz a leitura o arquivo Json e salva em conteudoJson
    fread(conteudoArquivo, 1, tamanhoArquivo, arquivo);
    // Coloca um '\0' para finalizar a string
    conteudoArquivo[tamanhoArquivo] = '\0';

    fclose(arquivo);
    // Retorna a estrutura de dados do Json e atribui em listaJson
    cJSON *listaJson = cJSON_Parse(conteudoArquivo);
    if (listaJson == NULL)
    {
        printf("Erro ao fazer o parsing do JSON.\n");
        free(conteudoArquivo);
        exit(-1);
    }

    cJSON_ReplaceItemInObject(listaJson, "nome", cJSON_CreateString(nomeJogo));
    cJSON_ReplaceItemInObject(listaJson, "quantidade", cJSON_CreateNumber(-1));
    cJSON_ReplaceItemInObject(listaJson, "preco", cJSON_CreateNumber(-1));
    cJSON_ReplaceItemInObject(listaJson, "finalizacao", cJSON_CreateNumber(-1));

    char *novoJson = cJSON_Print(listaJson);
    arquivo = abreArq(CAMINHO, "w");
    fprintf(arquivo, "%s", novoJson);
    // deleta o json e da free no arquivo onde tem todo o texto json
    cJSON_Delete(listaJson);
    free(conteudoArquivo);
    free(novoJson);
    fclose(arquivo);
    return;
}

void pedeFornecedor_wrapper(char *nomeJogo)
{
    int tam = strlen(nomeJogo);
    char nomeaux[50];
    strcpy(nomeaux, nomeJogo);
    for (int i = 0; i < tam; i++)
    {
        nomeaux[i] = tolower(nomeaux[i]);
    }
    pedeFornecedor(nomeaux);
    return;
}

void recebeRequisicao(Estoque *lista)
{

    Estoque *aux = lista;

    FILE *arquivo = abreArq(CAMINHO, "r");
    // Pega o tamanho do arquivo indo com o ponteiro ate o final usando seek
    fseek(arquivo, 0, SEEK_END);
    long tamanhoArquivo = ftell(arquivo);
    // Volta o ponteiro para o inicio do arquivo
    fseek(arquivo, 0, SEEK_SET);
    // Realiza um malloc para conteudoArquivo, onde vai ser salvo o arquivo todo json
    char *conteudoArquivo = (char *)malloc(tamanhoArquivo + 1);
    // Faz a leitura o arquivo Json e salva em conteudoJson
    fread(conteudoArquivo, 1, tamanhoArquivo, arquivo);
    // Coloca um '\0' para finalizar a string
    conteudoArquivo[tamanhoArquivo] = '\0';
    fclose(arquivo);

    cJSON *listaJson = cJSON_Parse(conteudoArquivo);
    if (listaJson == NULL)
    {
        printf("Erro ao fazer o parsing do JSON.\n");
        free(conteudoArquivo);
        exit(-1);
    }
    // cJSONnome = cJSON_GetObjectItem(root, "nome");
    cJSON *finalizacao = cJSON_GetObjectItem(listaJson, "finalizacao");
    cJSON *preco = cJSON_GetObjectItem(listaJson, "preco");
    cJSON *quantidade = cJSON_GetObjectItem(listaJson, "quantidade");
    if (finalizacao == NULL)
    {
        printf("Erro ao obter o item 'finalizacao' do JSON.\n");
        cJSON_Delete(listaJson);
        free(conteudoArquivo);
        exit(-1);
    }
    // printf("%d\n", finalizacao->valueint);

    if (quantidade->valueint == -1 && preco->valuedouble > 0)
    {
        arquivo = abreArq(CAMINHO, "w");
        cJSON_ReplaceItemInObject(listaJson, "quantidade", cJSON_CreateNumber(1));
        char *novoJson = cJSON_Print(listaJson);
        arquivo = abreArq(CAMINHO, "w");
        fprintf(arquivo, "%s", novoJson);
        fclose(arquivo);
    }

    if (finalizacao->valueint == 1)
    {

        cJSON *nome = cJSON_GetObjectItem(listaJson, "nome");
        cJSON *preco = cJSON_GetObjectItem(listaJson, "preco");
        char nomeAux[50];
        strcpy(nomeAux, nome->valuestring);

        for (int i = 0; i < 1; i++)
        {
            nomeAux[i] = toupper(nomeAux[i]);
        }
        while (aux != NULL)
        {

            if (strcmp(nomeAux, aux->dados.nome) == 0)
            {
                aux->dados.disponibilidade++;
                aux->dados.demanda = 0;
                saldo -= preco->valueint;
                arquivo = abreArq(CAMINHO, "w");
                cJSON_ReplaceItemInObject(listaJson, "nome", cJSON_CreateString(""));
                cJSON_ReplaceItemInObject(listaJson, "quantidade", cJSON_CreateNumber(-1));
                cJSON_ReplaceItemInObject(listaJson, "preco", cJSON_CreateNumber(-1));
                cJSON_ReplaceItemInObject(listaJson, "finalizacao", cJSON_CreateNumber(-1));
                char *novoJson = cJSON_Print(listaJson);
                arquivo = abreArq(CAMINHO, "w");
                fprintf(arquivo, "%s", novoJson);
                fclose(arquivo);
                break;
            }

            aux = aux->prox;
        }
    }
    cJSON_Delete(listaJson);
    free(conteudoArquivo);
}