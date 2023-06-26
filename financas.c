#include "financas.h"
#include <string.h>

/* Funcao: editaValor
// Requisitos:
     Acrescer valor exposto no sistema.
     Decrescer valor armazenado no sistema.

    - Assertivas de entrada:
        Valores que abrajam o tipo float.
    - Assertivas de sa�da:
        O arquivo edita ficando com o novo valor.

Interface com usu�rio: "Antigo saldo: <valorLido>"   "Novo saldo: <novoValor>\n\n"   "Erro: parametro '0' nao permitido ! Abortando.\n"
*/
void editaValor(float valorInserido) { // valor inserido pelo usuario a ser calculado com o valor registrado em arquivo que pode ser negativo ou positivo.
    float novoValor, valorLido = 0;  // variaveis para valor calculado 
    if (valorInserido == 0) {
        printf("Erro: parametro '0' nao permitido ! Abortando.\n");
        exit(-100001);
    }
    valorLido = consultaValor(); // adquire valor atual do saldo

    novoValor = valorLido + valorInserido; // Calcula novo valor

    // Escreve novo valor
    FILE* arqWrite = abreArq("balance.txt", "w"); // inicia escrita
    fprintf(arqWrite, "%f", novoValor); // escreve o valor calculado
    fclose(arqWrite); // fecha arquivo

    printf("Novo saldo: %.2f\n\n", novoValor);
}






/* Funcao: consultaValor
// Requisitos:
     Consultar saldo da locadora.

    - Assertivas de entrada:
        Void

    - Assertivas de sa�da:
        Retorna valor float representando o saldo.

Interface com usu�rio: "Valor consultado: <QUERY>\n\n"
*/
float consultaValor() {
    float query; // inicializa variavel a deter valor da busca
    FILE* arq = abreArq("balance.txt", "r"); // recebe o arquivo aberto no modo read
    fscanf(arq, "%f", &query);  // escaneia o numero para dentro da var query  
    fclose(arq); // fecha arq

    printf("Valor consultado: %.2f\n", query);

    return query; // retorna valor escaneado
}

float inicializaSaldo(){
    float query; // inicializa variavel a deter valor da busca
    FILE* arq = abreArq("balance.txt", "r"); // recebe o arquivo aberto no modo read
    fscanf(arq, "%f", &query);  // escaneia o numero para dentro da var query  
    fclose(arq); // fecha arq
    //printf("Valor consultado: %.2f\n", query);
    return query; // retorna valor escaneado
}

void salvaSaldo(){
    // Salva o saldo
    FILE* arqWrite = abreArq("balance.txt", "w"); // inicia escrita
    fprintf(arqWrite, "%f", saldo); // escreve o valor calculado
    fclose(arqWrite); // fecha arquivo
    //printf("Saldo salvo com sucesso\n");
}
