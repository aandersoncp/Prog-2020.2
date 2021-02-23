#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>

typedef struct{
	char nome[13];
	int pontos;
	char jogada[30];
} Jogador;

/*void iniciar(Jogador *participantes, int numero_jogadores){
	for(int i = 0; i < numero_jogadores; i++){
		participantes[i] = NULL;
	}
}*/

int str_tamanho(char *s) {
	int i = 0;
	while (s[i] != '\0'){
		i++;
	}
	return i;
}

int validar_nome(char *nome){
	while(str_tamanho(nome) > 12){
		printf("(ATENÇÃO) Digite o nome do jogador número com até 12 caracteres: \n");
		scanf("%s", nome);
	}
	return 1;
}

int validar_jogada(char *jogada, char letra){
	while(str_tamanho(jogada) > 30){
		printf("(ATENÇÃO) Digite uma jogada com até 30 caracteres: \n");
		scanf("%s", jogada);
	}
	while((int) jogada[0] != (int) letra && (int) jogada[0] != ((int) letra) + 32){
		printf("(ATENÇÃO) Digite uma jogada que comece com a letra %c: \n", letra);
		scanf("%s", jogada);
	}
	return 1;
}

void inserir_jogador(Jogador *participantes, char *nome, int i){
	strcpy(participantes[i].nome, nome);
}

void inserir_jogada(Jogador *participantes, char *jogada, int i){
	strcpy(participantes[i].jogada, jogada);
}

int buscar(Jogador *participantes, char *nome, int numero_jogadores){
	for(int i = 0; i < numero_jogadores; i++){
		if(strcmp(participantes[i].nome, nome) == 0){
			return i;
		}
	}
	return 0;
}

int achou(int *ordem, int n, int num){
	for(int i = 0; i < n; i++){
		if(ordem[i] == num){
			return 1;
		}
	}
	return 0;
}

void ordem_rodada(int *ordem, int n){
	int num, i = 0;
	for(int j = 0; j < n; j++){
		ordem[j] = -1;
	}
	while(i < n){
		num = rand()%(n);
		while(achou(ordem, n, num)){
			num = rand()%(n);
		}
		ordem[i] = num;
		//printf("%d", num);
		i++;
	}
	//printf("\n");
}

/*void calcular_pontos(Jogador *participantes, int n){
	char jogada_rodada[30];
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			if(str_tamanho(participantes[i].jogada) == str_tamanho(participantes[j].jogada)){

			}
		}
	}
}*/

int main(){
	int numero_jogadores;
	char nome_participante[50];
	char jogada_rodada[30];
	char letras[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *categorias[] = {"COMIDA", "ANIMAIS", "PESSOAS", "CIDADES", "PROFISSÕES"};
	int letra_rodada, categoria_rodada;
	srand(time(NULL)); 

	printf("Digite o número de jogadores (no mínimo 2 e no máximo 10): \n");
	scanf("%d", &numero_jogadores);
	while(numero_jogadores < 1 || numero_jogadores > 10){
		printf("Digite o número de jogadores (NO MÍNIMO 2 E NO MÁXIMO 10): \n");
		scanf("%d", &numero_jogadores);
	}
	Jogador participantes[numero_jogadores];
	
	int ordem[numero_jogadores], ordem_categoria[5];
	ordem_rodada(ordem_categoria, 5);

	//iniciar(participantes, numero_jogadores);
	for(int i = 0; i < numero_jogadores; i++){
		printf("Digite o nome do jogador número %d: \n", (i + 1));
		scanf("%s", nome_participante);
		
		validar_nome(nome_participante);
		inserir_jogador(participantes, nome_participante, i);
	}
	printf("\n");

	for(int i = 0; i < numero_jogadores; i++){
		printf("Jogador(%d): %s\n", (i + 1), participantes[i].nome);
	}
	printf("\n");

	for(int i = 0; i < 5; i++){
		letra_rodada = rand()%(26);
		printf("Letra da rodada: %c\n", letras[letra_rodada]);
		printf("Categoria: %s\n", categorias[ordem_categoria[i]]);
		ordem_rodada(ordem, numero_jogadores);
		printf("Ordem dos jogadores na rodada %d\n", (i + 1));
		for(int k = 0; k < numero_jogadores; k++){
			printf("Jogador %d: ", ordem[k]);
			printf("%s\n", participantes[ordem[k]].nome);
		}
		printf("\n");
		for(int k = 0; k < numero_jogadores; k++){
			printf("Jogador %d: %s, digite sua resposta:\n", ordem[k], participantes[ordem[k]].nome);
			scanf("%s", jogada_rodada);
			validar_jogada(jogada_rodada, letras[letra_rodada]);
			inserir_jogada(participantes, jogada_rodada, ordem[k]);
		}
	}
	return 0;
}
