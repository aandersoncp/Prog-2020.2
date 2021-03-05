#include <stdlib.h>
#include <stdio.h>
#include "intlst.h"

Lista *lst_inicializa() {
	return NULL;
}

int lst_inserir(Lista **ll, int i) {
	Lista *novo;
	
	novo = malloc(sizeof(Lista));
	if (novo == NULL)
		return 0;

	novo->info = i;
	novo->prox = NULL;

	if (*ll != NULL)
		novo->prox = *ll;
	*ll = novo;
		
	return 1;
}

void carregar(Lista **ll, char *nomearq){
	FILE *arq;
	int info;
	arq = fopen(nomearq, "r");
	if (arq == NULL){
		printf("Erro na abertura do arquivo\n");
		return;
	}
	while(fscanf(arq, "%d\n", &info) != EOF)
		lst_inserir(ll, info);

	fclose(arq);
}

void percorrer(Lista **ll){
	Lista *aux = *ll;
	if(*ll == NULL){
		return;
	} else {
		while(aux != NULL){
			printf("INFO: %d\n", aux->info);
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
		fprintf(arq, "%d\n", (*aux).info);
		aux = (*aux).prox;
	}

	fclose(arq);

	return;
}
