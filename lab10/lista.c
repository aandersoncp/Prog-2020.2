#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "intlst.h"

Lista *lst_inicializa() {
	return NULL;
}

int lst_inserir(Lista **ll, int matr, char *nome, int ddd, int tel, char* email, char tipo) {
	Lista *novo;
	
	novo = malloc(sizeof(Lista));
	if (novo == NULL)
		return 0;

	strcpy(novo->nome, nome);
	strcpy(novo->email, email);
	novo->matr= matr;
	novo->ddd = ddd;
	novo->tel = tel;
	novo->tipo = tipo;
	novo->prox = NULL;

	if (*ll != NULL)
		novo->prox = *ll;
	*ll = novo;
		
	return 1;
}

void carregar(Lista **ll, char *nomearq){
	FILE *arq;
	char nome[MAXNOME], email[MAXNOME], tipo;
	int matr, ddd, tel;
	arq = fopen(nomearq, "r");
	if (arq == NULL){
		printf("Erro na abertura do arquivo\n");
		return;
	}
	while(fscanf(arq, "%d\n%s\n%d\n%d\n%s\n%c", &matr, nome, &ddd, &tel, email, &tipo) != EOF){
		lst_inserir(ll, matr, nome, ddd, tel, email, tipo);
	}

	fclose(arq);
	printf("Carrega,ento feito com sucesso!\n");
}

void percorrer(Lista **ll){
	Lista *aux = *ll;
	if(*ll == NULL){
		return;
	} else {
		while(aux != NULL){
			printf("MATRÍCULA: %d\n", aux->matr);
			printf("NOME: %s\n", aux->nome);
			printf("E-MAIL: %s\n", aux->email);
			printf("TELEFONE: (%d) %d ", aux->ddd, aux->tel);
			if(aux->tipo == 'f' || aux->tipo == 'F'){
				printf("(fixo)\n");
			} else{
				printf("(celular)\n\n");
			}
			aux = aux->prox;
		}
	}
}

void salvar(Lista **ll, char *nomearq){
	FILE *arq;
	Lista *aux;

	aux = *ll;

	arq = fopen(nomearq, "w");

	if (arq == NULL){
		printf("Erro na abertura do arquivo\n");
		return;
	}

	while (aux != NULL) {
		fprintf(arq, "%d\n%s\n%d\n%d\n%s\n%c\n", (*aux).matr, (*aux).nome, (*aux).ddd, (*aux).tel, (*aux).email, (*aux).tipo);
		aux = (*aux).prox;
	}

	fclose(arq);
	printf("Contatos salvos com sucesso no arquivo %s!\n", nomearq);

	return;
}

void menu(Lista **ll, char *nomearq){

	char nome[MAXNOME], email[MAXNOME], tipo;
	int matr, ddd, tel;
	char comando;
	int sair = 0;

	system("clear");

	while (sair != 1) {
		printf("------ MENU ------\nESCOLHA UM DOS COMANDOS:\n;\nInserir novo contato (opção ‘I’);\nCarregar contatos de arquivo (opção ‘C’);\nListar nomes na agenda (opção ‘P’);\nSalvar os contatos em arquivo('S');\n*Para sair do Menu digite 'X'.\n\nEscolher opção: ");

		scanf(" %c", &comando);

		switch (comando) {
			case 'I':
				printf("\n> INSERIR CONTATO:\nDigite o nome (limitados a 100 caracteres): ");
				scanf("%s", nome);
				while(strlen(nome) > 100){
					printf("\n> INSERIR CONTATO:\nDigite o nome (limitados a 100 caracteres): ");
					scanf("%s", nome);
				}
				printf("Digite a Matrícula: ");
				scanf("%d", &matr);
				while(matr < 0){
					printf("Digite a Matrícula: ");
					scanf("%d", &matr);
				}
				printf("Digite o DDD: ");
				scanf("%d", &ddd);
				while(ddd < 0 && ddd < 100){
					printf("Digite o DDD: ");
					scanf("%d", &ddd);
				}
				printf("Digite o Telefone: ");
				scanf("%d", &tel);
				while(tel < 0 && tel < 1000000000){
					printf("Digite o Telefone: ");
					scanf("%d", &tel);
				}
				printf("Digite o Tipo do telefone (caractere – ‘C’ para celular ou ‘F’ para fixo): ");
				scanf(" %c", &tipo);
				while(tipo != 'C' && tipo != 'c' && tipo != 'F' && tipo != 'f'){
					printf("Digite o Tipo do telefone (caractere – ‘C’ para celular ou ‘F’ para fixo): ");
					scanf(" %c", &tipo);
				}
				printf("Digite o email (limitados a 100 caracteres): ");
				scanf("%s", email);
				printf("\n"); 
				lst_inserir(ll, matr, nome, ddd, tel, email, tipo);
				break;
			case 'i': 
				printf("\n> INSERIR CONTATO:\nDigite o nome (limitados a 100 caracteres): ");
				scanf("%s", nome);
				while(strlen(nome) > 100){
					printf("\n> INSERIR CONTATO:\nDigite o nome (limitados a 100 caracteres): ");
					scanf("%s", nome);
				}
				printf("Digite a Matrícula: ");
				scanf("%d", &matr);
				while(matr < 0){
					printf("Digite a Matrícula: ");
					scanf("%d", &matr);
				}
				printf("Digite o DDD: ");
				scanf("%d", &ddd);
				while(ddd < 0 && ddd < 100){
					printf("Digite o DDD: ");
					scanf("%d", &ddd);
				}
				printf("Digite o Telefone: ");
				scanf("%d", &tel);
				while(tel < 0 && tel < 1000000000){
					printf("Digite o Telefone: ");
					scanf("%d", &tel);
				}
				printf("Digite o Tipo do telefone (caractere – ‘C’ para celular ou ‘F’ para fixo): ");
				scanf(" %c", &tipo);
				while(tipo != 'C' && tipo != 'c' && tipo != 'F' && tipo != 'f'){
					printf("Digite o Tipo do telefone (caractere – ‘C’ para celular ou ‘F’ para fixo): ");
					scanf(" %c", &tipo);
				}
				printf("Digite o email (limitados a 100 caracteres): ");
				scanf("%s", email);
				printf("\n"); 
				lst_inserir(ll, matr, nome, ddd, tel, email, tipo);
				break;
			case 'P':
				percorrer(ll); 
				break;
			case 'p':
				percorrer(ll); 
				break;
			case 'C': 
				carregar(ll, nomearq); 
				break;
			case 'c': 
				carregar(ll, nomearq);
				break;
			case 'S': 
				salvar(ll, "contatos_salvos.txt"); 
				break;
			case 's': 
				salvar(ll, "contatos_salvos.txt");
				break;
			case 'X':
				sair = 1; 
				break;
			case 'x':
				sair = 1; 
				break;
			default: 
				printf("ERRO: Comando inválida, tente novamente.\n\n");
				break;
		}
		
		if(sair != 1){
			sair = voltaraomenu();
		}
	}

}


int voltaraomenu(){
	char voltar;
	printf("Voltar ao menu (s\\n)? ");
	scanf(" %c", &voltar);
	if(voltar == 'N' || voltar == 'n'){
		return 1;
	} else if(voltar == 'S' || voltar == 's'){
		system("clear");
		return 0;
	} else{
		voltaraomenu();
	}
}
