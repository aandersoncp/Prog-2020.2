#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXNOME 100

typedef struct lista {
	char nome[MAXNOME];
	char email[MAXNOME];
	char tipo;
	int matr;
	int ddd;
	int tel;
	struct lista *prox;
	struct lista *ant;
} Lista;


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
				printf("(fixo)\n\n");
			} else{
				printf("(celular)\n\n");
			}
			aux = aux->prox;
		}
	}
}

int agd_inserir_inicio(Lista **ll, int matr, char *nome, int ddd, int tel, char* email, char tipo) {
	Lista *novo;
	
	novo = malloc(sizeof(Lista));
	if(novo == NULL){
		return 0;
	}

	strcpy(novo->nome, nome);
	strcpy(novo->email, email);
	novo->matr = matr;
	novo->ddd = ddd;
	novo->tel = tel;
	novo->tipo = tipo;
	novo->prox = NULL;
	novo->ant = NULL;

	novo->prox = *ll;
	if (*ll != NULL){
		(*ll)->ant = novo;
	}

	*ll = novo;
	
	//percorrer(ll);

	return 1;
}

int agd_inserir_final(Lista **ll, int matr, char *nome, int ddd, int tel, char* email, char tipo) {
	Lista *novo, *aux = *ll;
	
	novo = malloc(sizeof(Lista));
	if(novo == NULL){
		return 0;
	}
	if(*ll != NULL){
		while(aux->prox != NULL){
			aux = aux->prox;
		}
	}

	strcpy(novo->nome, nome);
	strcpy(novo->email, email);
	novo->matr= matr;
	novo->ddd = ddd;
	novo->tel = tel;
	novo->tipo = tipo;
	novo->prox = NULL;
	novo->ant = NULL;

	if(*ll == NULL){
		*ll = novo;
	} else {
		aux->prox = novo;
		novo->ant = aux;
	}
	
	//percorrer(ll);
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
		agd_inserir_final(ll, matr, nome, ddd, tel, email, tipo);
	}

	fclose(arq);
	printf("Carregamento feito com sucesso!\n");
}


void remover(Lista **ll, char* nome){
	Lista *aux = *ll;
	if(*ll == NULL){
		return;
	} else {
		while(aux != NULL){
			if(strcmp(aux->nome, nome) == 0){
				if((aux->ant) != NULL){
					(aux->ant)->prox = aux->prox;
				} else {
					*ll = aux->prox;
				}
				if((aux->prox) != NULL){
					(aux->prox)->ant = aux->ant;
				}
				free(aux);
				return;
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

int comparar(char *nome1, char* nome2){
	int tamanho = strlen(nome1);
	if(strlen(nome2) < tamanho){
		tamanho = strlen(nome2);
	}
	for(int i = 0; i < tamanho; i++){
		if(tolower(nome1[i]) > tolower(nome2[i])){
			return 1;
		} else if(tolower(nome1[i]) < tolower(nome2[i])){
			return 0;
		}
	}
	if(strlen(nome1) == tamanho){
		return 0;
	} else{
		return 1;
	}
}

void agd_ordenar(Lista **ll){
	Lista *aux, *aux1, *aux2;
	aux = *ll;
	aux1 = aux;
	aux2 = aux;

	if(aux1 == NULL){
		printf("Lista vazia!\n");
		return;
	}

	printf("\n----LISTA NÃO ORDENADA----\n\n");
	percorrer(ll);

	while(aux2 != NULL){
		aux1 = aux2;
		while(aux1 != NULL){
			if(comparar(aux1->nome, aux2->nome)){
				if((aux2->prox) != NULL){
					(aux2->prox)->ant = aux2->ant;
				}
				(aux2->ant)->prox = aux2->prox;
				(aux2->prox) = aux1;
				(aux2->ant) = aux1->ant;
				if(aux1->ant != NULL){
					(aux1->ant)->prox = aux2;
				} else{
					*ll = aux2;
				}
				(aux1->ant) = aux2;
			}
			aux1 = aux1->ant;
		}
		aux2 = aux2->prox;
	}
	printf("\n\n----LISTA ORDENADA----\n\n");
	percorrer(ll);
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

void menu(Lista **ll, char *nomearq){

	char nome[MAXNOME], email[MAXNOME], tipo;
	int matr, ddd, tel;
	char comando;
	int sair = 0;

	system("clear");

	while (sair != 1) {
		printf("------ MENU ------\nESCOLHA UM DOS COMANDOS:\n\nInserir novo contato no início(opção ‘I’);\nInserir novo contato no fim(opção ‘F’);\nCarregar contatos de arquivo (opção ‘C’);\nRemover contato (opção 'R')\nListar nomes na agenda (opção ‘P’);\nOrdenar por ordem alfabética os nomes na agenda (opção ‘O’);\nSalvar os contatos em arquivo('S');\n*Para sair do Menu digite 'X'.\n\nEscolher opção: ");

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
				agd_inserir_inicio(ll, matr, nome, ddd, tel, email, tipo);
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
				agd_inserir_inicio(ll, matr, nome, ddd, tel, email, tipo);
				break;
			case 'F':
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
				agd_inserir_final(ll, matr, nome, ddd, tel, email, tipo);
				break;
			case 'f': 
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
				agd_inserir_final(ll, matr, nome, ddd, tel, email, tipo);
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
			case 'O':
				agd_ordenar(ll);
				break;
			case 'o':
				agd_ordenar(ll);
				break;
			case 'R':
				printf("\n> REMOVER CONTATO:\nDigite o nome do contato para ser removido: ");
				scanf("%s", nome);
				remover(ll, nome);
				break;
			case 'r':
				printf("\n> REMOVER CONTATO:\nDigite o nome do contato para ser removido: ");
				scanf("%s", nome);
				remover(ll, nome);
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


int main(int narg, char *argv[]) {
	Lista *l;

	char nome[MAXNOME], email[MAXNOME], tipo;
	int matr, ddd, tel;
	
	l = lst_inicializa();
	
	menu(&l, argv[1]);
	
	return EXIT_SUCCESS;
}
