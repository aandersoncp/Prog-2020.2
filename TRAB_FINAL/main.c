#include <stdio.h>
#include <stdlib.h>

typedef struct no_arvore{
	int chave;
	float info;
	struct no_arvore *pai, *esq, *dir;
} Arvore;

typedef struct no_lista{
	int chave;
	float info;
	struct no_lista *prox, *ant;
} Lista;

void iniciar_lista(Lista **l){
	*l = NULL;
}

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
	printf("ADICIONANDO: (%d, %f)\n", chave, valor);
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
		printf("%f \n", aux->info);
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

int busca_binária(int *vetor, int chave, int inicio, int fim){
	int n = fim - inicio;
	n = n/2;
	

}

int busca_sequencial(int *vetor, int n, int chave){
	for(int i = 0, i < n; i++){
		if(chave == vetor[i]){
			return 1;
		}
	}
	return 0;
}


int main(){
	Lista *ll;
	Arvore *raiz;
	int *vetor;

	int m, n = 0;

	iniciar_arvore(&raiz);
	iniciar_lista(&ll);

	inserir_no_arvore(&raiz, 5, 2.2);
	inserir_no_arvore(&raiz, 4, 3.3);
	inserir_no_arvore(&raiz, 3, 23.2);
	inserir_no_arvore(&raiz, 2, 6.7);
	inserir_no_arvore(&raiz, 6, 4.2);
	inserir_no_arvore(&raiz, 7, 1.13);
	inserir_no_arvore(&raiz, 8, 14.0);

	m = maior_chave(&raiz);
	printf("m = %d\n", m);

	percurso_em_ordem(&raiz, vetor, &n);

	if(buscar_arvore(&raiz, 7)){
		printf("Achei!\n");
	} else{
		printf("Não achei!\n");
	}

	printf("\n");
	for(int j = 0; j < n; j++){
		printf("%d\n", vetor[j]);
	}

	return 0;
}

/*
int buscar_arvore(Arvore **a, int chave){
	Arvore *aux;
	aux = *a;

	while(aux->chave != chave){
		if(aux->chave >= chave){
			aux = aux->esq;
		} else{
			aux = aux->dir;
		}
	}
	if(aux->chave == chave){
		return 1;
	} else {
		return 0;
	}
}
*/