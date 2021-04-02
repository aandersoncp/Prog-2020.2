#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "abb.h"
#include "listaduplaencad.h"
#include "config.h"


int busca_sequencial(int *vetor, int n, int chave){
	for(int i = 0; i < n; i++){
		if(chave == vetor[i]){
			return 1;
		}
	}
	return 0;
}

void comparador(Arvore **a, Lista **ll, int *vetor){
	int chave, aux1, aux2, encontrar, n = 0, buscar;
	float valor; 
	long double time1 = 0, time2 = 0, time3 = 0, time4 = 0;
	clock_t inicio, fim;
	srand(time(NULL));

	for(int i = 0; i < K; i++){
		iniciar_arvore(a);
		iniciar_lista(ll);
		inicio = clock();
		for(int j = 0; j < N; j++){
			chave = rand()%(100*N);
			//VERIFICAR SE A CHAVE É ÚNICA
			aux1 = rand()%(100*N);
			aux2 = rand()%(100*N);
			while(aux2 == 0){
				aux2 = rand()%(100*N);
			}
			valor = aux1/(float) aux2;
			inserir_no_arvore(a, chave, valor);
			lista_inserir(ll, chave, valor);
		}
		n = 0;
		//printf("\n");
		buscar = rand()%(100*N);
		percurso_em_ordem(a, vetor, &n);
		//printf("\n");
		fim = clock();
		time4 = time4 + (fim - inicio);

		inicio = clock();
		buscar_arvore(a, buscar);
		fim = clock();
		time1 = time1 + (fim - inicio);
		//liberar_arvore(a);

		inicio = clock();
		buscar_lista(ll, buscar);
		fim = clock();
		time2 = time2 + (fim - inicio);
		//liberar_lista(ll);

		inicio = clock();
		busca_sequencial(vetor, N, buscar);
		fim = clock();
		time3 = time3 + (fim - inicio);

		inicio = clock();
		liberar_arvore(a);
		liberar_lista(ll);
		fim = clock();
		time4 = time4 + (fim - inicio);
	}

	printf("Tempo de busca ABB: %Lf\n",time1/CLOCKS_PER_SEC);
	printf("Tempo de busca LISTA: %Lf\n",time2/CLOCKS_PER_SEC);
	printf("Tempo de busca sequencial VETOR: %Lf\n",time3/CLOCKS_PER_SEC);
	printf("Tempo restante: %Lf\n",time4/CLOCKS_PER_SEC);

}