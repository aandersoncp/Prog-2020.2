#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<ctype.h>
#include<math.h>
#include<pthread.h>
#include "jogo.h"

void validar_num_jogadores(int* numero_jogadores){
	while(*numero_jogadores < 1 || *numero_jogadores > 10){
		printf("Digite o número de jogadores (NO MÍNIMO 2 E NO MÁXIMO 10): \n");
		scanf("%d", numero_jogadores);
	}

}

int validar_nome(char *nome){
	while(strlen(nome) > 12){
		printf("(ATENÇÃO) Digite o nome do jogador número com até 12 caracteres: \n");
		scanf("%s", nome);
	}
	return 1;
}

int validar_jogada(char *jogada, char letra){
	while(strlen(jogada) > 30){
		printf("(ATENÇÃO) Digite uma jogada com até 30 caracteres: \n");
		scanf("%s", jogada);
	}
	while((int) jogada[0] != (int) letra && (int) jogada[0] != ((int) letra) + 32){
		printf("(ATENÇÃO) Digite uma jogada que comece com a letra %c: \n", letra);
		scanf("%s", jogada);
	}
	printf("\n-------JOGADA OK!-------\n");
	return 1;
}

void inserir_jogador(Jogador *participantes, char *nome, int i){
	strcpy(participantes[i].nome, nome);
}

void inserir_jogada(Jogador *participante, char *jogada, int i){
	strcpy(participante[i].jogada, jogada);
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

int comparacao(char *nome, char *aux){
	if(strlen(nome) == strlen(aux)){
		for(int i = 0; i < strlen(nome); i++){
			if( tolower(nome[i]) != tolower(aux[i])){
				return 0;
			}
		}
		return 1;
	}
	return 0;
}

void pontuacao(Jogador exemplo[], int n, double pontos[]){
	int iguais[n][n + 1];
	int igual, pontof, pontoc, pont = 0;
	double ponto;	

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(i == j){
				iguais[i][j] = 1;
			} else{
				iguais[i][j] = 0;
			}
		}
	}

	for(int i = 0; i < n; i++){
		if(iguais[i][i] == 1){
			igual = 1;
			for(int j = i + 1; j < n; j++){
				if(comparacao(exemplo[i].jogada, exemplo[j].jogada)){
					iguais[i][j] = 1;
					iguais[j][j] = 0;
					igual++;
				}
			}
			iguais[i][n] = igual;
		}
	}

	for(int i = 0; i < n; i++){
		ponto = strlen(exemplo[i].jogada)/(double)iguais[i][n];
		pontof = floor(strlen(exemplo[i].jogada)/(double)iguais[i][n]);
		if((ponto - pontof) < 0.5){
			pont = pontof;
		} else {
			pont = (pontof + 1);
		}
		if(iguais[i][i] == 1){
			pontos[i] += pont;
			for(int j = i + 1; j < n; j++){
				if(iguais[i][j] == 1){
					pontos[j] += pont;
				}
			}
		}
	}
	printf("\nRespostas:\n");
	for(int i = 0; i < n; i++){
		printf("Jogador (%d) %s: %s\n", (i + 1), exemplo[i].nome, exemplo[i].jogada);
	}
	printf("\n");

	printf("Pontuação\n");
	for(int i = 0; i < n; i++){
		printf("Jogador (%d) %s: %lf\n", (i + 1), exemplo[i].nome, pontos[i]);
	}
}

void * routine(void *arg){
	int r;
	int *contador = (int *)(arg);
	*contador = ((*contador)*2) + 8;
	while((*contador)--){
		//printf("%d\n", *contador);
		arg = (void *)(contador);
		sleep(1);
	}
	r = pthread_cancel(thread_idB);
	pthread_exit(arg);
}

void * routine2(void *arg){	
	scanf("%s", (char *)(arg));
	//aux_jogada = (char *)(arg);
	pthread_exit(arg);
}

void jogadores_nomes(Jogador *participantes, int numero_jogadores){
	char nome_participante[50];
	for(int i = 0; i < numero_jogadores; i++){
		printf("Digite o nome do jogador número %d: \n", (i + 1));
		scanf("%s", nome_participante);
		validar_nome(nome_participante);
		inserir_jogador(participantes, nome_participante, i);
	}
	for(int i = 0; i < numero_jogadores; i++){
		printf("Jogador(%d): %s\n", (i + 1), participantes[i].nome);
	}
	printf("\n");
	printf("\n");
}

void inic_pontos(double *pontos, int numero_jogadores){
	for(int i = 0; i < numero_jogadores; i++){
		pontos[i] = 0;
	}
}

/*
void entrada(Jogador jogador, char letra, int n){
	void * thread_resA;
	void * thread_resB;
	int rstatus, r, a = n, fim = 1;
	char jogada[30];
	
	rstatus = pthread_create (&thread_idA, NULL, routine, (void*)(&a));
	rstatus = pthread_create (&thread_idB, NULL, routine2, (void*)(jogada));

	while(fim){
		if(pthread_join(thread_idB, &thread_resB) == 0){
			r = pthread_cancel(thread_idA);
			fim = 0;
		}
	}
	//printf("Jogada: %s\n", jogada);
	validar_jogada(jogada, letra);
	inserir_jogada(jogador, jogada, a);
	printf("Jogada do jogador %s: %s\n", jogador.nome ,jogador.jogada);
}*/

void rodadas(int numero_jogadores, Jogador *participantes){
	int letra_rodada, categoria_rodada;
	int ordem[numero_jogadores], ordem_categoria[5];
	double pontos[numero_jogadores];
	char jogada_rodada[30];
	char letras[] = "ABCDEFGHIJLMNOPQRSTUVXZ";
	char *categorias[] = {"COMIDA", "ANIMAIS", "PESSOAS", "CIDADES", "PROFISSÕES"};
	void * thread_resA;
	void * thread_resB;
	int rstatus, r, a = numero_jogadores, fim;
	char jogada[30];

	ordem_rodada(ordem_categoria, 5);

	inic_pontos(pontos, numero_jogadores);

	for(int i = 0; i < 5; i++){
		letra_rodada = rand()%(23);
		printf("Categoria: %s com %c\n", categorias[ordem_categoria[i]], letras[letra_rodada]);
		ordem_rodada(ordem, numero_jogadores);
		printf("Ordem dos jogadores na rodada %d\n", (i + 1));
		for(int k = 0; k < numero_jogadores; k++){
			printf("Jogador %d: ", ordem[k]);
			printf("%s\n", participantes[ordem[k]].nome);
		}
		printf("\n");
		for(int k = 0; k < numero_jogadores; k++){
			fim = 1;
			printf("Categoria: %s com %c\n", categorias[ordem_categoria[i]], letras[letra_rodada]); //
			printf("Jogador %d: %s, digite sua resposta:\n", (ordem[k] + 1), participantes[ordem[k]].nome);
	
			rstatus = pthread_create (&thread_idA, NULL, routine, (void*)(&a));
			rstatus = pthread_create (&thread_idB, NULL, routine2, (void*)(jogada));

			while(fim){
				if(pthread_join(thread_idB, &thread_resB) == 0){
					r = pthread_cancel(thread_idA);
					fim = 0;
				}
			}	
			//printf("Jogada: %s\n", jogada);
			validar_jogada(jogada, letras[letra_rodada]);
			inserir_jogada(participantes, jogada, ordem[k]);
			printf("Jogada do jogador %s: %s\n", participantes[ordem[k]].nome ,participantes[ordem[k]].jogada);
		}
			//scanf("%s", jogada_rodada);
			//validar_jogada(jogada_rodada, letras[letra_rodada]);
			//inserir_jogada(participantes[ordem[k]], jogada_rodada);
			//system("clear"); //
		pontuacao(participantes, numero_jogadores, pontos);
		printf("\n");
	}
}
