#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "abb.h"
#include "listaduplaencad.h"
#include "config.h"

/*
int busca_binaria(int *vetor, int chave, int inicio, int fim){
	int n = fim - inicio;
	n = n/2;


}*/



int main(){
	Lista *ll;
	Arvore *raiz;
	int *vetor;
	long double time1 = 0, time2 = 0, time3 = 0, time4 = 0;
	srand(time(NULL));
	
	iniciar_arvore(&raiz);
	iniciar_lista(&ll);

	comparador(&raiz, &ll, vetor);

	return 0;
}