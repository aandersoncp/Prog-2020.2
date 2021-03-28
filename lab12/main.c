#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "lista_polimortica.h"

int main(){
	Lista *l;
	
	inicializar(&l);
	
	menu(&l);

	return 0;
}