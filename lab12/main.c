#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
	int chave;
	int tipo;
	void* info;
	struct node *prox, *ant;
} Lista;

#define T_INT 0
#define T_FLOAT 1
#define T_C_CHAR 2
#define T_CHAR 3

void inicializar(Lista **l){
	*l = NULL;
}

int inserir_no(Lista **l, Lista *novo){
	Lista *aux;

	if(*l == NULL){
		*l = novo;
		novo->prox = novo;
		novo->ant = novo;
		return 1;
	}

	if((*l)->chave >= novo->chave){
		if((*l)->chave == novo->chave){
			free(novo->info);
			free(novo);
			return 0; 
		}
		novo->prox = *l;
		novo->ant = (*l)->ant;
		((*l)->ant)->prox = novo;
		(*l)->ant = novo;
		(*l) = novo;
		return 1;
	}

	aux= (*l)->ant;
	if(novo->chave >= aux->chave){
		if(aux->chave == novo->chave){
			free(novo->info);
			free(novo);
			return 0;
		}
		aux->prox = novo;
		novo->ant = aux;
		novo->prox = *l;
		(*l)->ant = novo;
		return 1;
	}

	aux = *l;
	while(aux->prox->chave < novo->chave){
		aux = aux->prox;
	}

	if(aux->chave == novo->chave){
		free(novo->info);
		free(novo);
		return 0;
	}
	novo->prox = aux->prox;
	novo->ant = aux;
	novo->prox->ant = novo;
	aux->prox = novo;
	return 1;
}

int inserir_inteiro(Lista **l, int chave, int val){
	Lista *novo;

	novo = (Lista*)malloc(sizeof(Lista));
	if(novo == NULL){
		printf("Erro, sem espaço!\n");
		return 0;
	}
	novo->info = malloc(sizeof(int));
	if(novo->info == NULL){
		free(novo);
		return 0;
	}
	*((int*)novo->info) = val;
	novo->tipo = T_INT;
	novo->chave = chave;

	inserir_no(l, novo);
}

int inserir_p_flutuante(Lista **l, int chave, float val){
	Lista *novo;

	novo = (Lista*)malloc(sizeof(Lista));
	if(novo == NULL){
		printf("Erro, sem espaço!\n");
		return 0;
	}
	novo->info = malloc(sizeof(float));
	if(novo->info == NULL){
		free(novo);
		return 0;
	}
	*((float*)novo->info) = val;
	novo->tipo = T_FLOAT;
	novo->chave = chave;

	inserir_no(l, novo);
}

int inserir_c_caracteres(Lista **l, int chave, char* val){
	Lista *novo;
	novo = (Lista*)malloc(sizeof(Lista));
	if(novo == NULL){
		printf("Erro, sem espaço!\n");
		return 0;
	}

	novo->info = malloc(sizeof(char)*strlen(val));
	if(novo->info == NULL){
		free(novo);
		return 0;
	}

	//*((float*)novo->info) = val;
	strcpy((char*)novo->info, val);
	novo->tipo = T_C_CHAR;
	novo->chave = chave;

	inserir_no(l, novo);
}

int inserir_caractere(Lista **l, int chave, char val){
	Lista *novo;
	novo = (Lista*)malloc(sizeof(Lista));
	if(novo == NULL){
		printf("Erro, sem espaço!\n");
		return 0;
	}

	novo->info = malloc(sizeof(char));
	if(novo->info == NULL){
		free(novo);
		return 0;
	}
	
	*((char*)novo->info) = val;
	novo->tipo = T_C_CHAR;
	novo->chave = chave;

	inserir_no(l, novo);
}

int obter_tipo (Lista **l, int chave){
	Lista *aux = *l;
	int i = 0;

	while(aux->chave != chave){
		aux = aux->prox;
		if(aux->chave == (*l)->chave){
			printf("Chave inexistente!\n");
			return 0;
		}
	}

	if(aux->tipo == 0){
		printf("Tipo: INTEIRO.\n");
	}else if(aux->tipo == 1){
		printf("Tipo: PONTO FLUTUANTE.\n");
	} else if(aux->tipo == 2){
		printf("Tipo: CADEIA DE CARACTERES.\n");
	} else{
		printf("Tipo: CARACTERE.\n");
	}

	return aux->tipo;
}

int obter_inteiro(Lista **l, int chave){
	Lista *aux = *l;

	if(aux->chave != chave){
		aux = aux->prox;
	}

	while(aux->chave != chave){
		aux = aux->prox;
		if(aux->chave == (*l)->chave){
			printf("Chave inexistente!\n");
			return -99999;
		}
	}

	if(aux->tipo == 0){
		printf("Informação: %d\n", *(int*)aux->info);
		return *(int*)aux->info;
	} else{
		printf("Erro! Tipo não é inteiro!\n");
		return -99999;
	}
}

float obter_p_flutuante(Lista **l, int chave){
	Lista *aux = *l;

	while(aux->chave != chave){
		aux = aux->prox;
		if(aux->chave == (*l)->chave){
			printf("Chave inexistente!\n");
			return -99999;
		}
	}

	if(aux->tipo == 1){
		printf("Informação: %f\n", *(float*)aux->info);
		return *(float*)aux->info;
	} else{
		printf("Erro! Tipo não é ponto flutuante!\n");
		return -99999;
	}
}

char *obter_c_caracteres (Lista **l, int chave){
	Lista *aux = *l;

	while(aux->chave != chave){
		aux = aux->prox;
		if(aux->chave == (*l)->chave){
			printf("Chave inexistente! Tipo não é cadeia de caracteres!\n");
			return NULL;
		}
	}

	if(aux->tipo == 2){
		printf("Informação: %s\n", (char*)aux->info);
		return aux->info;
	} else{
		printf("Erro!\n");
		return NULL;
	}
}

char obter_caractere(Lista **l, int chave){
	Lista *aux = *l;

	while(aux->chave != chave){
		aux = aux->prox;
		if(aux->chave == (*l)->chave){
			printf("Chave inexistente!\n");
			return '\0';
		}
	}

	if(aux->tipo == 2){
		printf("Informação: %c\n", *(char*)aux->info);
		return *(char*)aux->info;
	} else{
		printf("Erro! Tipo não é caractere!\n");
		return '\0';
	}
}

void listar_elementos (Lista **l){
	Lista *aux = *l;

	if(aux->tipo == 0){
		printf("CHAVE: %d - INFO: %d\n", aux->chave, *(int*)aux->info);
	}else if(aux->tipo == 1){
		printf("CHAVE: %d - INFO: %f\n", aux->chave, *(float*)aux->info);
	} else if(aux->tipo == 2){
		printf("CHAVE: %d - INFO: %s\n", aux->chave, (char*)aux->info);
	} else{
		printf("CHAVE: %d - INFO: %c\n", aux->chave, *(char*)aux->info);
	}

	aux = aux->prox;

	while(aux->chave != (*l)->chave){
		if(aux->tipo == 0){
			printf("CHAVE: %d - INFO: %d\n", aux->chave, *(int*)aux->info);
		}else if(aux->tipo == 1){
			printf("CHAVE: %d - INFO: %f\n", aux->chave, *(float*)aux->info);
		} else if(aux->tipo == 2){
			printf("CHAVE: %d - INFO: %s\n", aux->chave, (char*)aux->info);
		} else{
			printf("CHAVE: %d - INFO: %c\n", aux->chave, *(char*)aux->info);
		}
		aux = aux->prox;
	}
}


int voltaraomenu(){
	char voltar;
	printf("Voltar ao menu (s\\n)? ");
	scanf(" %c", &voltar);
	if(voltar == 'N' || voltar == 'n'){
		return 1;
	} else if(voltar == 'S' || voltar == 's'){
		system("clear");
		return 0;
	} else{
		voltaraomenu();
	}
}

void menu(Lista **ll){

	char *s, c;
	int i, chave;
	float f;
	char comando;
	int sair = 0;

	system("clear");

	while (sair != 1) {
		printf("------ MENU ------\nESCOLHA UM DOS COMANDOS:\n\nInserir inteiro(opção ‘1’);\nInserir ponto flutuante(opção ‘2’);\nInserir caractere(opção ‘3’);\nInserir cadeia de caracteres (opção '4')\nListar elementos (opção ‘5’);\nObter inteiro de um elemento (opção ‘6’);\nObter ponto flutuante de um elemento (opção ‘7’);\nObter cadeia de caractere de um elemento (opção ‘8’);\nObter caractere de um elemento (opção ‘9’);\n*Para sair do Menu digite 'X'.\n\nEscolher opção: ");

		scanf(" %c", &comando);

		switch (comando) {
			case '1':
				printf("\n> INSERIR INTEIRO:\nDigite um inteiro para ser a chave: ");
				scanf("%d", &chave);
				printf("\nDigite um inteiro como informação: ");
				scanf("%d", &i);
				inserir_inteiro(ll, chave, i);
				break;
			case '2':
				printf("\n> INSERIR PONTO FLUTUANTE:\nDigite um inteiro para ser a chave: ");
				scanf("%d", &chave);
				printf("\nDigite um ponto flutuante como informação: ");
				scanf("%f", &f);
				inserir_p_flutuante(ll, chave, f);
				break;
			case '3': 
				printf("\n> INSERIR CARACTERE:\nDigite um inteiro para ser a chave: ");
				scanf("%d", &chave);
				setbuf(stdin, NULL);
				printf("\nDigite um caractere como informação: ");
				scanf("%c", &c); 
				inserir_caractere(ll, chave, c);
				break;
			case '4': 
				printf("\n> INSERIR CADEIA DE CARACTERES:\nDigite um inteiro para ser a chave: ");
				scanf("%d", &chave);
				printf("\nDigite uma cadeia de caractere como informação: ");
				scanf("%s", s);
				inserir_c_caracteres(ll, chave, s);
				break;
			case '5': 
				listar_elementos(ll);
				break;
			case '6': 
				printf("\n> OBTER INTEIRO:\nDigite a chave(um inteiro) do elemento: ");
				scanf("%d", &chave);
				obter_inteiro(ll, chave);
				break;
			case '7': 
				printf("\n> OBTER PONTO FLUTUANTE:\nDigite a chave(um inteiro) do elemento: ");
				scanf("%d", &chave);
				obter_p_flutuante(ll, chave);
				break;
			case '8': 
				printf("\n> OBTER CADEIA DE CARACTERES:\nDigite a chave(um inteiro) do elemento: ");
				scanf("%d", &chave);
				obter_c_caracteres(ll, chave);
				break;
			case '9': 
				printf("\n> OBTER CARACTERE:\nDigite a chave(um inteiro) do elemento: ");
				scanf("%d", &chave);
				obter_caractere(ll, chave);
				break;
			case 'X':
				sair = 1; 
				break;
			case 'x':
				sair = 1; 
				break;
			default: 
				printf("ERRO: Comando inválida, tente novamente.\n\n");
				break;
		}
		if(sair != 1){
			sair = voltaraomenu();
		}
	}
}


int main(){
	Lista *l;
	
	inicializar(&l);
	
	menu(&l);

	return 0;
}
