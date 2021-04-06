#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "abb.h"
#include "listaduplaencad.h"
#include "config.h"


#define N 600
#define K 1605000



int main(){
	Lista *ll;
	Arvore *raiz;
	int vetor[N];
	long double time1 = 0, time2 = 0, time3 = 0, time4 = 0;
	srand(time(NULL));
	
	iniciar_arvore(&raiz);
	iniciar_lista(&ll);

	comparador(&raiz, &ll, vetor, N, K);

	return 0;
}