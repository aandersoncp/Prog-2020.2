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

void inicializar(Lista **l);

int inserir_no(Lista **l, Lista *novo);

int inserir_inteiro(Lista **l, int chave, int val);

int inserir_p_flutuante(Lista **l, int chave, float val);

int inserir_c_caracteres(Lista **l, int chave, char* val);

int inserir_caractere(Lista **l, int chave, char val);

int obter_tipo (Lista **l, int chave);

int obter_inteiro(Lista **l, int chave);

float obter_p_flutuante(Lista **l, int chave);

char *obter_c_caracteres (Lista **l, int chave);

char obter_caractere(Lista **l, int chave);

void listar_elementos (Lista **l);

int voltaraomenu();

void menu(Lista **ll);
