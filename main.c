#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "reutilizavel.h"
#include "financas.h"
#include "estoque.h"
#include "fornecedor.h"

float saldo;

int main(void) {
	
	// variaveis quando cadastra cliente for ser utilizado
	saldo = inicializaSaldo();
	//printf("Saldo: %.2f\n", saldo);

	int opcaoInterface = 0;
	float testaFinancas=0;
	//char* nomeArquivo = "estoque.json";
	Estoque* lista = leArquivoJSON("estoque.json");

	int opcaoMenu = -10; // variavel para menu
	// variaveis para alterar estoque
	// Interface	
	while (1) { // Loop
		recebeRequisicao(lista);
		printf("Menu - Bem vindo a Locadora !\n");
		printf("  1) Cadastrar Cliente\n");
		printf("  2) Alterar estoque\n");
		printf("  3) Exibir estoque\n");
		printf("  4) Registrar aluguel\n");
		printf("  5) Exibir saldo\n");
		printf("  6) Sair\n\n");

		// Manutenciador de eventos
		scanf("%d", &opcaoMenu);// Seleciona opcao
		switch (opcaoMenu) {
		case 1:
			printf("  ==> 1 - CADASTRAR CLIENTE\n");
			cadastraCliente();
			break;
		case 2:
			printf("  ==> 2 - ALTERAR ESTOQUE\n");
			alteraEstoque(lista);

			break;
		case 3:
			//printf("  ==> 2 - ALTERAR ESTOQUE\n");
			imprimeEstoque(lista);

			break;
		case 4:
			printf("  ==> 4 - REGISTRO DE ALUGUEL\n");
			registraAluguel(lista);
			break;

		case 5:
			printf("  ==> 5 - Exibe Saldo\n");
			printf("Saldo: R$ %.2f \n\n", saldo);
			break;
		case 6:
			printf("   Saindo\n");
			estoqueJson(lista);
			salvaSaldo();
			exit(1);
			break;
		default:
			break;
		}
	}


	return 0;
}