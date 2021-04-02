#define MAXNOME 100

typedef struct no_lista{
	int chave;
	float info;
	struct no_lista *prox, *ant;
} Lista;

void iniciar_lista(Lista **ll);

void percorrer(Lista **ll);

int buscar_lista(Lista **ll, int chave);

int lista_inserir(Lista **ll, int chave, float info);

void agd_ordenar(Lista **ll);

void liberar_lista(Lista **ll);