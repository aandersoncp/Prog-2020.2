#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "abb.h"

void iniciar_arvore(Arvore **a){
	*a = NULL;
}

void inserir_no_arvore(Arvore **a, int chave, float valor){
	Arvore *novo, *aux;
	novo = (Arvore*)malloc(sizeof(Arvore));
	int posicao = 0;

	if(novo == NULL){
		printf("Erro! Falta de espaço!\n");
		return;
	}

	novo->chave = chave;
	novo->info = valor;
	novo->esq = NULL;
	novo->dir = NULL;

	if(*a == NULL){
		*a = novo;
		return;
	}
	aux = *a;

	while(posicao == 0){
		if(aux->chave >= chave){
			if(aux->esq == NULL){
				novo->pai = aux;
				aux->esq = novo;
				posicao = 1;
			} else {
				aux = aux->esq;
			}
		}
		else {
			if(aux->dir == NULL){
				novo->pai = aux;
				aux->dir = novo;
				posicao = 1;
			} else {
				aux = aux->dir;
			}
		}
	}
	//printf("ADICIONANDO: (%d, %f)\n", chave, valor);
	return;
}

int maior_chave(Arvore **a){
	Arvore *aux;
	aux = *a;

	while(aux->dir != NULL){
		aux = aux->dir;
	}

	return aux->chave;
}

void percurso_em_ordem(Arvore **a, int *vetor, int *i){
	Arvore *aux;
	aux = *a;
	if( aux != NULL){
		percurso_em_ordem(&(aux->esq), vetor, i);
		//printf("CHAVE: %d - VALOR: %f \n",aux->chave, aux->info);
		vetor[*i] = (aux->chave);
		(*i)++;
		percurso_em_ordem(&(aux->dir), vetor, i);
	}
}

int buscar_arvore(Arvore **a, int chave){
	Arvore *aux;
	aux = *a;

	if(aux != NULL){
		if(aux->chave == chave){
			return 1;
		} else{
			if(aux->chave > chave){
				buscar_arvore(&(aux->esq), chave);
			} else if(aux->chave < chave){
				buscar_arvore(&(aux->dir), chave);
			}
		}
	} else{
		return 0;
	}
}

/*
void liberar_arvore(Arvore **a){ //Função que libera os nós de uma árvore
	Arvore *aux1, *aux2;
	aux1 = *a;
	if(aux1->pai == NULL){
		free(aux1);
		return;
	}
	aux2 = aux1->pai;

	if(aux1 != NULL){
		liberar_arvore(&(aux1->esq));
		liberar_arvore(&(aux1->dir));
		free(aux1);
	}
	return;
}
*/

Arvore* liberar_arvore(Arvore **a){ //Função que libera os nós de uma árvore
	Arvore *aux1, *aux2;
	aux1 = *a;
	if(aux1 != NULL){
		liberar_arvore(&(aux1->esq));
		liberar_arvore(&(aux1->dir));
		free(aux1);
	}
	return NULL;
}