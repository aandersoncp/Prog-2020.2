#define MAXNOME 100

typedef struct lista {
	char nome[MAXNOME];
	char email[MAXNOME];
	char tipo;
	int matr;
	int ddd;
	int tel;
	struct lista *prox;
} Lista;

Lista *lst_inicializa();
int lst_inserir(Lista **ll, int matr, char *nome, int ddd, int tel, char* email, char tipo);
void salvar(Lista **ll, char *nomearq);
void percorrer(Lista **ll);
void carregar(Lista **ll, char *nomearq);
void menu(Lista **ll, char *nomearq);
int voltaraomenu();
