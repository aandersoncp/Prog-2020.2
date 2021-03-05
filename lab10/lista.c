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
	char nome[MAXNOME], email[MAXNOME+1], tipo;
	int matr, ddd, tel;
	arq = fopen(nomearq, "r");
	if (arq == NULL){
		printf("Erro na abertura do arquivo\n");
		return;
	}
	while(fscanf(arq, "%d\n%s\n%d\n%d\n%s\n%c", &matr, nome, &ddd, &tel, email, &tipo) != EOF)
		lst_inserir(ll, matr, nome, ddd, tel, email, tipo);

	fclose(arq);
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

	return;
}
