#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "listaduplaencad.h"

int main(int narg, char *argv[]) {
	Lista *l;

	char nome[MAXNOME], email[MAXNOME], tipo;
	int matr, ddd, tel;
	
	l = lst_inicializa();
	
	menu(&l, argv[1]);
	
	return EXIT_SUCCESS;
}
