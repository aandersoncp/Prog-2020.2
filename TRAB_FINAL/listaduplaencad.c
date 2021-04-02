#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "listaduplaencad.h"


void iniciar_lista(Lista **ll){
	*ll = NULL;
}

void percorrer(Lista **ll){
	Lista *aux = *ll;
	if(*ll == NULL){
		printf("Lista vazia!\n");
		return;
	} else {
		while(aux != NULL){
			//printf("CHAVE: %d - INFO: %f\n", aux->chave, aux->info);
			aux = aux->prox;
		}
	}
}

int buscar_lista(Lista **ll, int chave){
	Lista *aux;
	aux = *ll;

	while(aux != NULL){
		if(aux->chave == chave){
			return 1;
		}
		aux = aux->prox;
	}
	return 0;
}

int lista_inserir(Lista **ll, int chave, float info) {
	Lista *novo;
	
	novo = malloc(sizeof(Lista));
	if(novo == NULL){
		return 0;
	}

	novo->chave = chave;
	novo->info = info;
	novo->prox = NULL;
	novo->ant = NULL;

	novo->prox = *ll;
	if (*ll != NULL){
		(*ll)->ant = novo;
	}

	*ll = novo;

	return 1;
}

void liberar_lista(Lista **ll){
	Lista *aux1, *aux2;
	aux1 = *ll;
	while(aux1->prox != NULL){
		aux1 = aux1->prox;
	}
	aux2 = aux1->ant;
	while(aux2 != NULL){
		free(aux1);
		aux1 = aux2;
		aux2 = aux2->ant;
	}
	free(*ll);
	return;
}