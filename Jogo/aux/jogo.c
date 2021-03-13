#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<ctype.h>
#include<math.h>
#include<pthread.h>
#include "jogo.h"

void validar_num_jogadores(int* numero_jogadores){ // FUNÇÃO QUE VALIDA O NÚMERO DE JOGADORES, CASO A ENTRADA SEJA UMA LETRA HÁ PROBLEMA
	while(*numero_jogadores < 1 || *numero_jogadores > 10){
		printf("Digite o número de jogadores (NO MÍNIMO 2 E NO MÁXIMO 10): \n");
		scanf("%d", numero_jogadores);
	}
}

int validar_nome(char *nome){ // FUNÇÃO QUE VALIDA OS NOMES DOS JOGADORES
	while(strlen(nome) > 12){
		printf("(ATENÇÃO) Digite o nome do jogador número com até 12 caracteres: \n");
		scanf("%s", nome);
	}
	return 1;
}

int validar_jogada(char *jogada, char letra){ // FUNÇÃO QUE VALIDA AS JOGADAS, VERIFICA SE A JOGADA TEM MAIS DE 30 POSIÇÕES OU SE COMEÇA COM A LETRA CERTA
	while(strlen(jogada) > 30){
		printf("(ATENÇÃO) Digite uma jogada com até 30 caracteres: \n");
		scanf("%s", jogada);
	}
	while((int) jogada[0] != (int) letra && (int) jogada[0] != ((int) letra) + 32){
		printf("(ATENÇÃO) Digite uma jogada que comece com a letra %c: \n", letra);
		scanf("%s", jogada);
	}
	return 1;
}

void inserir_jogador(Jogador *participantes, char *nome, int i){ // FUNÇÃO QUE COLOCA O NOME NO STRUCT JOGADOR
	strcpy(participantes[i].nome, nome);
}

void inserir_jogada(Jogador *participante, char *jogada, int i){ // FUNÇÃO QUE COLOCA A JOGADA NO STRUCT JOGADOR
	strcpy(participante[i].jogada, jogada);
}

int achou(int *ordem, int n, int num){ // FUNÇÃO QUE DETECTA SE ENCONTROU UM VALOR NO VETOR ORDEM
	for(int i = 0; i < n; i++){
		if(ordem[i] == num){
			return 1;
		}
	}
	return 0;
}

void ordem_rodada(int *ordem, int n){ // FUNÇÃO QUE ORDENA A ORDEM DOS JOGADORES EM CADA RODADA
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
		i++;
	}
}

int comparacao(char *nome, char *aux){ // FUNÇÃO VERIFICA SE AS STRINGS SÃO IGUAIS
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

void pontuacao(Jogador exemplo[], int n, double pontos[]){ // FUNÇÃO QUE CALCULA A PONTUAÇÃO DOS JOGADORES EM CADA RODADA
	int iguais[n][n + 1];
	int igual, pontof, pontoc, pont = 0;
	double ponto;	

	for(int i = 0; i < n; i++){ // MATRIZ QUE AJUDA NA COMPARAÇÃO DAS JOGADAS, INICIALIZA COM UMA MATRIZ IDENTIDADE
		for(int j = 0; j < n; j++){
			if(i == j){
				iguais[i][j] = 1;
			} else{
				iguais[i][j] = 0;
			}
		}
	}

	for(int i = 0; i < n; i++){ // PARTE QUE FAZ A COMPARAÇÃO ENTRE AS JOGADAS, CASO A JOGADA DO JOGADOR I É IGUAL AO DO JOGADOR J ENTÃO A POSIÇÃO JJ RECEBE 0 E A POSIÇÃO IJ RECEBE 1, OU SEJA, NO FINAL SE NA LINHA I HÁ MAIS DE UM ELEMENTO IJ COM 1 ENTAÕ AS JOGADAS J SERÃO IGUAIS A I
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

	for(int i = 0; i < n; i++){ // PARTE QUE ATRIBUI OS PONTOS AO JOGADOR
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

	printf("\n##### Respostas: #####\n");
	for(int i = 0; i < n; i++){
		printf("Jogador (%d) %s: %s\n", (i + 1), exemplo[i].nome, exemplo[i].jogada);
	}

	printf("\n##### Pontuação: #####\n");
	for(int i = 0; i < n; i++){
		printf("Jogador (%d) %s: %.1lf\n", (i + 1), exemplo[i].nome, pontos[i]);
	}

	printf("\n##### Tempo: #####\n");
	for(int i = 0; i < n; i++){
		printf("Jogador (%d) %s: %d segundos\n", (i + 1), exemplo[i].nome, exemplo[i].tempo_jogador);
	}
}

void * routine(void *arg){ // FUNÇÃO DA THREAD QUE CONTA O TEMPO, SE O TEMPO ACABAR HÁ O CANCELAMENTO DA OUTRA THREAD(QUE ESPERA A JOGADA)
	int r;
	int *contador = (int *)(arg);
	while((*contador)--){
		arg = (void *)(contador);
		sleep(1);
	}
	r = pthread_cancel(thread_idB);
	pthread_exit(arg);
}

void * routine2(void *arg){	// FUNÇÃO DA THREAD QUE ESPERA A JOGADA
	scanf("%s", (char *)(arg));
	pthread_exit(arg);
}

void jogadores_nomes(Jogador *participantes, int numero_jogadores){ // FUNÇÃO QUE RECEBE OS NOMES DOS JOGADORES
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

void inic_pontos(double *pontos, int numero_jogadores){ // FUNÇÃO QUE INICIALIZA COM O VETOR DE PONTOS COM ZEROS
	for(int i = 0; i < numero_jogadores; i++){
		pontos[i] = 0;
	}
}


void rodadas(int numero_jogadores, Jogador *participantes){ // FUNÇÃO QUE ADMINISTRA AS RODADAS
	int letra_rodada, categoria_rodada;
	int ordem[numero_jogadores], ordem_categoria[5];
	double pontos[numero_jogadores];
	char jogada_rodada[30];
	char letras[] = "ABCDEFGHIJLMNOPQRSTUVXZ";
	char *categorias[] = {"COMIDA", "ANIMAIS", "PESSOAS", "CIDADES", "PROFISSÕES"};
	void * thread_resA;
	void * thread_resB;
	int rstatus, r, num, x = numero_jogadores, fim, vencedor = 0, vencedores[numero_jogadores];
	char jogada[30];
	
	ordem_rodada(ordem_categoria, 5);

	inic_pontos(pontos, numero_jogadores);

	for(int k = 0; k < numero_jogadores; k++){
		participantes[k].tempo_jogador = 0;
		vencedores[k] = 0;
	}

	for(int i = 0; i < 5; i++){
		x = numero_jogadores;
		num = x;
		letra_rodada = rand()%(23);
		printf("----- Categoria: %s com %c -----\n", categorias[ordem_categoria[i]], letras[letra_rodada]);
		ordem_rodada(ordem, numero_jogadores);
		printf("----- Ordem dos jogadores na rodada %d -----\n", (i + 1));
		for(int k = 0; k < numero_jogadores; k++){
			printf("Jogador %d: ", (ordem[k] + 1));
			printf("%s\n", participantes[ordem[k]].nome);
		}
		printf("\n");
		for(int k = 0; k < numero_jogadores; k++){
			fim = 1;
			printf("\n----- Categoria: %s com %c -----\n", categorias[ordem_categoria[i]], letras[letra_rodada]); //
			num = (x*2 + 8);
			printf("Jogador %d: %s, digite sua resposta, você tem %d segundos para responder:\n", (ordem[k] + 1), participantes[ordem[k]].nome, (x*2 + 8));

			rstatus = pthread_create (&thread_idA, NULL, routine, (void*)(&(num)));  // CRIAÇÃO DA THREAD QUE CONTA O TEMPO
			rstatus = pthread_create (&thread_idB, NULL, routine2, (void*)(jogada)); // CRIAÇÃO DA THREAD QUE ESPERA A JOGADA
			
			while(fim){
				if(pthread_join(thread_idB, &thread_resB) == 0){ // SE UMA JOGADA É DIGITADA ENTÃO A THREAD QUE ESPERA A JOGADA É TERMINADA E A QUE CONTA O TEMPO É CANCELADA
					r = pthread_cancel(thread_idA);
					fim = 0;
				}
			}
			if(num == -1){
				inserir_jogada(participantes, "", ordem[k]);
			} else {
				participantes[ordem[k]].tempo_jogador += (x*2 + 8 - num);
				validar_jogada(jogada, letras[letra_rodada]);
				inserir_jogada(participantes, jogada, ordem[k]);
			}
			num = x--;
		}
		system("clear"); 
		pontuacao(participantes, numero_jogadores, pontos);
		for(int i = 0; i < numero_jogadores; i++){ // PARTE QUE VERIFICA QUEM É O VENCEDOR
			if(participantes[i].pontos > participantes[vencedor].pontos){
				vencedor = i;
				for(int k = 0; k < numero_jogadores; k++){
					vencedores[k] = 0;
				}
				vencedores[i] = 1;		
			} else if(participantes[i].pontos == participantes[vencedor].pontos){
				if(participantes[i].tempo_jogador < participantes[vencedor].tempo_jogador){
					vencedor = i;
					for(int k = 0; k < numero_jogadores; k++){
						vencedores[k] = 0;
					}
				} else if(participantes[i].tempo_jogador == participantes[vencedor].tempo_jogador){
					vencedores[i] = 1;
					vencedores[vencedor] = 1;
				}
			}
		}
		printf("\n");
		for(int k = 0; k < numero_jogadores; k++){
			if(vencedores[k] == 1){
				printf("Vencedor: %s\n", participantes[k].nome);
			}
		}
		printf("\n");
	}
}
