#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"
#include "cJson.h"
#include "cliente.h"
#include "reutilizavel.h"
#include "financas.h"
#include "fornecedor.h"

// comentario dfghjdfghj
//   sdfgjdvcvb


/*
	Compilacao: gcc -o "nome_executavel" "nome_arquivo.c" cJSON/cJSON.c -IcJSON -LcJSON -lcjson
	
	Coisas que faltam:
		- Criar um editor de no da lista encadeada, onde passo codigo e ele pergunta o que tem que ser editado
*/

/*  Nome: criaNo
    Objetivo: Funcao auxiliar para criar um novo n�
    Requisitos: 
	    Criar um estoque

    Assertivas de entrada 
     **********
    Assertivas de saida 
     - o programa aborta com saida -1.
*/
Estoque* criaNo(Jogo dado) {
    Estoque* novo = (Estoque*)malloc(sizeof(Estoque));
    if (novo == NULL) {
        printf ("Erro na alocacao de memoria da criaNo\n");
        exit (-1);
    } 
    novo->dados = dado;
    novo->prox = NULL;

    return novo;
}

/*  Nome: insereNo
    Objetivo: Insere um n� no in�cio da lista encadeada

    Requisitos: 
	    Criar um estoque

    Assertivas de entrada 
     **********
    Assertivas de saida 
     **********
*/
void insereNo(Estoque** lista, Jogo dado) {
    Estoque* novoNo = criaNo(dado);
    novoNo->prox = *lista;
    *lista = novoNo;
}

/*  Nome: leArquivoJSON
    Objetivo: L� o arquivo JSON e cria a lista encadeada 

    Requisitos: 
	*******

    Assertivas de entrada 
     **********
    Assertivas de saida 
     - o programa aborta com saida -1.
*/
Estoque* leArquivoJSON(char* nomeArquivo) {
	// ========= Tratamento do arquivo =========

	// Realiza a abertura do arquivo
    FILE* arquivo = abreArq(nomeArquivo, "r");

	// Pega o tamanho do arquivo indo com o ponteiro ate o final usando seek
    fseek(arquivo, 0, SEEK_END);
    long tamanhoArquivo = ftell(arquivo);
	// Volta o ponteiro para o inicio do arquivo
    fseek(arquivo, 0, SEEK_SET);

	// Realiza um malloc para conteudoArquivo, onde vai ser salvo o arquivo todo json
    char* conteudoArquivo = (char*)malloc(tamanhoArquivo + 1);
	// Faz a leitura o arquivo Json e salva em conteudoJson
    fread(conteudoArquivo, 1, tamanhoArquivo, arquivo);
	// Coloca um '\0' para finalizar a string
    conteudoArquivo[tamanhoArquivo] = '\0';

    fclose(arquivo);

	// ========= Inclusao na lista encadeada =========

	// Retorna a estrutura de dados do Json e atribui em listaJson
    cJSON* listaJson = cJSON_Parse(conteudoArquivo);
    if (listaJson == NULL) {
        printf("Erro ao fazer o parsing do JSON.\n");
        free(conteudoArquivo);
        exit(-1);
    }

    Estoque* lista = NULL;
    cJSON* noJson = NULL;

    cJSON_ArrayForEach(noJson, listaJson) {
		// Pega os elementos para serem adicionados e coloca em um auxiliar
        cJSON* nomeJson = cJSON_GetObjectItem(noJson, "nome");
        cJSON* codigoJson = cJSON_GetObjectItem(noJson, "codigo");
        cJSON* precoJson = cJSON_GetObjectItem(noJson, "preco");
        cJSON* dispJson = cJSON_GetObjectItem(noJson, "disponibilidade");
        cJSON* demandaJson = cJSON_GetObjectItem(noJson, "demanda");
        

        if (nomeJson && codigoJson && dispJson) {
			// atribui os elementos na struct jogo
            Jogo jogo;
			strcpy(jogo.nome, nomeJson->valuestring);
            jogo.codigo = codigoJson->valueint;
            jogo.disponibilidade = dispJson->valueint;
            jogo.preco = precoJson->valuedouble;
            jogo.demanda = demandaJson->valueint;

			// adiciona na lista encadeada, passando a struct preenchida
            insereNo(&lista, jogo);
        }
    }

	// deleta o json e da free no arquivo onde tem todo o texto json
    cJSON_Delete(listaJson);
    free(conteudoArquivo);

    return lista;
}

/*  Nome: imprimeEstoque
    Objetivo: Imprimir o estoque 

    Requisitos: 
	- Exibir o estoque.

    Assertivas de entrada 
     **********
    Assertivas de saida 
     - o programa aborta com saida -1.
*/
void imprimeEstoque(Estoque* lista) {
    if(lista == NULL){
        printf("Lista vazia\n");
        exit(-1);
    }
    Estoque* aux = lista;
    printf("==== Estoque ====\n");
    while (aux != NULL) {
        printf("Codigo: %d - Nome: %s - Preco: %.2f - Disponibilidade: %d", aux->dados.codigo, aux->dados.nome, aux->dados.preco, aux->dados.disponibilidade);
        if (aux->dados.disponibilidade == 0)
            printf(" - Demanda: %d", aux->dados.demanda);
        printf("\n");

        aux = aux->prox;
    }
    printf("\n");
}

Estoque* alteraEstoque(Estoque* lista){

    Jogo dado;
    int codigo;
    //printf("==== Estoque ====\n");
    imprimeEstoque(lista);

    printf("\nDigite o codigo do produto a ser alterado: ");
    scanf("%d", &codigo);
    //printf("\n%d", codigo);

    Estoque* aux = lista;
    for(int i = 0; aux != NULL; i++){
        if(aux->dados.codigo == codigo){
            printf("\n== Produto a ser alterado ==\n");
            printf("Nome: %s\nCodigo: %d\nDisponibilidade: %d\n", aux->dados.nome,aux->dados.codigo, aux->dados.disponibilidade);
            int x; 

            printf("\n== Alteracao ==");
            printf("\n1 - Nome\n2- Codigo\n3- Preco\n4- Disponibilidade");
            printf("\nEscolha o campo a ser alterado: ");
            scanf("%d", &x);
            
            switch (x)
            {
                char auxNome[20];
            case 1:
                printf("Digite o novo nome: ");
                scanf(" %19[^\n]", auxNome);
                strcpy(aux->dados.nome, auxNome);
                printf("\nNome alterado\n");
                break;
            case 2:
                //printf("Altera Codigo\n");
                printf("Digite o valor do codigo: ");
                scanf("%d", &aux->dados.codigo);
                printf("\nCodigo alterado\n");
                break;
            case 3:
                //printf("Altera Codigo\n");
                printf("Digite o valor do preco: ");
                scanf("%f", &aux->dados.preco);
                printf("\nCodigo alterado\n");
                break;
            case 4:
                printf("Digite o valor da disponibilidade: ");
                scanf("%d", &aux->dados.disponibilidade);
                printf("\nDisponibilidade alterada\n");
                break;
            
            default:
                break;
            }
            break;
        }
        aux = aux->prox;
    }
    

    return lista;
}


/*  Nome: geraJson
    Objetivo: Coloca um bloco de texto em um arquivo Json 

    Requisitos: 
	- *******.

    Assertivas de entrada 
     **********
    Assertivas de saida 
     - **********
*/

void geraJson(char* texto, char* caminho) {
    FILE* arq = abreArq(caminho, "w");

    fputs(texto, arq);
    fclose(arq);

    printf("Arquivo JSON criado com sucesso: %s\n", caminho);
}

/*  Nome: estoqueJson
    Objetivo: Transformar a lista encadeada em um arquivo Json

    Requisitos: 
	 ********

    Assertivas de entrada 
     **********
    Assertivas de saida 
     - o programa aborta com saida -1 e -2.
*/
void estoqueJson(Estoque* lista) {
    if(lista == NULL){
        printf("Lista vazia\n");
        exit(-1);
    }
    cJSON* listaJson = cJSON_CreateArray();
    Estoque* aux = lista;

    while (aux != NULL) {
        cJSON* noJson = cJSON_CreateObject();
        cJSON_AddStringToObject(noJson, "nome", aux->dados.nome);
        cJSON_AddNumberToObject(noJson, "codigo", aux->dados.codigo);
        cJSON_AddNumberToObject(noJson, "preco", aux->dados.preco);
        cJSON_AddNumberToObject(noJson, "disponibilidade", aux->dados.disponibilidade);
        cJSON_AddNumberToObject(noJson, "demanda", aux->dados.demanda);
        cJSON_AddItemToArray(listaJson, noJson);
        aux = aux->prox;
    }

    char* textoJson = cJSON_Print(listaJson);
    if(textoJson == NULL){
        printf("Erro na transformacao da lista em string (estoqueJson)\n");
        exit(-2);
    }
	geraJson(textoJson, "estoque.json");
}

int buscaLista(Estoque* lista, int codigo){
    Estoque* aux = lista;
    for(int i = 0; aux != NULL; i++){
        if(aux->dados.codigo == codigo){
            if(aux->dados.disponibilidade == 0){
                aux->dados.demanda++;
                if(aux->dados.demanda >= 3){
                    // Solicita para o fornecedor
                    printf("Solicitado para o fornecedor\n");
                    pedeFornecedor_wrapper(aux->dados.nome);
                }
                return -1;
            }
            else
                return 1;
        }
        aux = aux->prox;
    }
    return 0;
}

void registraAluguel(Estoque* lista) {
    /*
        Coisas p/ fzr:
            4 - Se a demanda for acima de 3, pede para o fornecedor
            5 - Se o jogo nao existir na base de dados, mandar uma nota p/ os fornecedores e criar um espaco para o jogo
    */


	char cpf[12];     // variaveis para registrar aluguel
    int dias = 0, codigo, aux = 0;
    while(aux == 0){
        printf("  	Qual codigo do jogo ?\n");
        scanf("%d", &codigo);
        //printf("%d\n", codigo);
        aux = buscaLista(lista, codigo);
        //printf("%d\n", aux);
        if(aux == 0){
            printf("Jogo nao encontrado\n");
            imprimeEstoque(lista);
        }
        if(aux == -1){
            printf("\nJogo sem disponibilidade\n\n");
            return;
        }
            
    }
    aux = 0;
    //printf("%d\n", aux);
    
    while(aux == 0){
        printf("     Quantos dias o alguel (1 ou 7 dias)?\n");
        scanf("%d", &dias);
        if (dias != 1 && dias != 7) {
            printf("O aluguel nao e de 7 nem de 1 dia.\n");
        }
        else
            aux = 1;

    }
    aux = 0;
    //printf("%d\n", aux);

    
    if(dias == 7){
        while(aux == 0){
                // conferir cadastro
                printf("    Qual cpf do cliente ?\n");
                scanf(" %11[^\n]", cpf);
            if (strlen(cpf) != 11) {           // se cpf diferente de 11 digitos
                printf("CPF SEM 11 DIGITOS\n");
                printf("cpf inserido: %s - %d digitos", cpf, strlen(cpf));
            }
            else
                aux = confereCPF(cpf);
                if(aux == -1){
                    printf("O cliente nao esta cadastrado, cadastre ele primeiro\n\n");
                    return;
                }
        }
    }
    else
        strcpy(cpf, "");

    Estoque* auxL = lista;
    for(int i = 0; auxL != NULL; i++){
        if(auxL->dados.codigo == codigo){
            auxL->dados.disponibilidade--;
            saldo += auxL->dados.preco;
            break;
        }
        auxL = auxL->prox;
    }
    
	FILE* file = abreArq("listaAlugueis.txt", "a"); 
	fprintf(file, "%s | %d | %s | %d\n", cpf, dias, __DATE__, codigo);
	fclose(file);
	printf("Dados salvos !\n");

    printf("\n     /\n");
			printf("   \\/ Aluguel registrado com sucesso !\n");
}