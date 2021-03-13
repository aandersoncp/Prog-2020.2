typedef struct{
	char nome[13];
	int pontos;
	char jogada[30];
	double tempo_jogador;
	int pontuac[5];
} Jogador;

pthread_t thread_idA;
pthread_t thread_idB;

void validar_num_jogadores(int* numero_jogadores);

int validar_nome(char *nome);

int validar_jogada(char *jogada, char letra);

void inserir_jogador(Jogador *participantes, char *nome, int i);

void inserir_jogada(Jogador *participante, char *jogada, int i);

//int buscar(Jogador *participantes, char *nome, int numero_jogadores);

int achou(int *ordem, int n, int num);

void ordem_rodada(int *ordem, int n);

int comparacao(char *nome, char *aux);

void pontuacao(Jogador exemplo[], int n, double pontos[], int k, char *categorias[], int *ordem_categoria);

void * routine(void *arg);

void * routine2(void *arg);

void jogadores_nomes(Jogador *participantes, int numero_jogadores);

void inic_pontos(double *pontos, int numero_jogadores);

void entrada(Jogador jogador, char letra, int n);

void rodadas(int numero_jogadores, Jogador *participantes);

