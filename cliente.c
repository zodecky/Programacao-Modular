#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "reutilizavel.h"

/* Cadastra cliente */

/* Requisitos
	- Cadastrar um cliente em algum arquivo com os dados: nome, cpf, celular e endereco.
*/

/* Assertivas de entrada
	 - Lidar com os dados de um cliente.
   Assertivas de saida
	 - O programa aborta com saída -1.
	 - O programa nao retorna nada.
*/
// Interface com o usuario: "nome | cpf | celular | endereco"       "Dados guardados"       "CPF SEM 11 DIGITOS"   "NOME VAZIO"     "CELULAR VAZIO"    "ENDERECO COM MENOS DE 9 DIGITOS"      "ENDERECO COM MENOS DE 9 DIGITOS"



void cadastraCliente() { // Recebe no parametros 'nome', 'cpf', 'celular' e 'endereco', respectivamente, o nome, cpf, celular e endereco do cliente. 
	char nome[40], endereco[40], cpf[20], celular[20];// variaveis para cadastrar cliente
	//long int cpf;
	int aux = 0;
	printf("     -  Cadastrando cliente...\n");
	while(aux == 0){
		printf("     Qual nome do cliente ?\n");
		scanf(" %[^\n]", nome);
		aux = 1;
		if (strlen(nome) < 3) {
			printf("Nome pequeno demais para ser cadastrado\n\n");
			aux = 0;
		}
	}
	aux = 0;
	while(aux == 0){
		printf("    Qual cpf do cliente ?\n");
		scanf(" %11[^\n]", cpf);
		aux = 1;
		if (strlen(cpf) != 11) {           // se cpf diferente de 11 digitos
			printf("CPF SEM 11 DIGITOS\n\n");
			//printf("%d", strlen(cpf));
			aux = 0;
		}
		if(confereCPF(cpf) == 1){
			printf("Esse CPF ja foi cadastrado\n");
			return;
		}
		
	}
	strcat(cpf, "\0");
	aux = 0;
	while(aux == 0){
		printf("  	Qual celular do cliente ?\n");
		scanf(" %[^\n]", celular);
		aux = 1;
		if (celular == "") {
			printf("CELULAR VAZIO\n");
			aux = 0;
		}
	}

	aux = 0;
	while(aux == 0){
		printf("  	Qual endereco do cliente ?\n");
		scanf(" %[^\n]", endereco);
		aux = 1;
		if (strlen(endereco) < 9) {
			printf("ENDERECO COM MENOS DE 9 DIGITOS\n");
			aux = 0;
		}
	}
	

	printf("%s - %s - %s - %s\n", nome, cpf, celular, endereco);
	

	FILE* file = abreArq("clientes.txt", "a");
	fprintf(file, "%s | %s | %s | %s\n", cpf, nome, celular, endereco);

	fclose(file);
	printf("Dados guardados !\n");
	printf("\n     /\n");
	printf("   \\/ Cliente cadastrado com sucesso !\n");
	return;
}


int confereCPF(char* cpf){
    FILE* arq = abreArq("clientes.txt", "r");
    char linha[300];
    char *campo;
    char auxCpf[100];
	int auxCpf1, auxCpf2;
	
    // Lê cada linha do arquivo
    while (fgets(linha, 300, arq) != NULL) {
        // Extrai os campos separados por |
        campo = strtok(linha, "|");
        if (campo != NULL) {
            strcpy(auxCpf, campo);
            campo = strtok(NULL, "|");
        }

		// /printf("CPF: %s\n", auxCpf);
		auxCpf1 = atoi(cpf);
		auxCpf2 = atoi(auxCpf);
		if (auxCpf1 == auxCpf2){
			return 1;
		}

        // Imprime os valores atribuídos às variáveis
        
        //printf("\n");
    }
    // Fecha o arquivo
    fclose(arq);
	return -1;
}
