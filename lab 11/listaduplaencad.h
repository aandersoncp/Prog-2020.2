#define MAXNOME 100

typedef struct lista {
	char nome[MAXNOME];
	char email[MAXNOME];
	char tipo;
	int matr;
	int ddd;
	int tel;
	struct lista *prox;
	struct lista *ant;
} Lista;


Lista *lst_inicializa();

void percorrer(Lista **ll);

int agd_inserir_inicio(Lista **ll, int matr, char *nome, int ddd, int tel, char* email, char tipo);

int agd_inserir_final(Lista **ll, int matr, char *nome, int ddd, int tel, char* email, char tipo);

void carregar(Lista **ll, char *nomearq);

void agd_remover(Lista **ll, char* nome);

void salvar(Lista **ll, char *nomearq);

int comparar(char *nome1, char* nome2);

void agd_ordenar(Lista **ll);

int voltaraomenu();

void menu(Lista **ll, char *nomearq);