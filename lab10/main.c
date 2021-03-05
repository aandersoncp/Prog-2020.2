#include <stdlib.h>
#include <stdio.h>
#include "intlst.h"

int main(int narg, char *argv[]) {
	Lista *l;
	
	l = lst_inicializa();
	
	if (lst_inserir(&l, 01, "josé", 85, 87878787, "jose@mail.com", 'c')){
		printf("Inserido com sucesso.\n");
	}
	else{
		printf("Falha ao inserir.\n");
	}

	if (lst_inserir(&l, 02, "maria", 88, 32868686, "maria@mail.com", 'f'))
		printf("Inserido com sucesso.\n");
	else
		printf("Falha ao inserir.\n");

	if (lst_inserir(&l, 03, "francisco", 88, 32328686, "frank@mail.com", 'f'))
		printf("Inserido com sucesso.\n");
	else
		printf("Falha ao inserir.\n");

	percorrer(&l);
	printf("\n");
	carregar(&l, argv[1]);
	salvar(&l, "teste");
	percorrer(&l);
	
	return EXIT_SUCCESS;
}

