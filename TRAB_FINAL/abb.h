typedef struct no_arvore{
	int chave;
	float info;
	struct no_arvore *pai, *esq, *dir;
} Arvore;

void iniciar_arvore(Arvore **a);

void inserir_no_arvore(Arvore **a, int chave, float valor);

int maior_chave(Arvore **a);

void percurso_em_ordem(Arvore **a, int *vetor, int *i);

int buscar_arvore(Arvore **a, int chave);

Arvore* liberar_arvore(Arvore **a);