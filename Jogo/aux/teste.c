#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<ctype.h>
#include<math.h>
#include<pthread.h>
#include "jogo.h"

int main(){
	int numero_jogadores;
	srand(time(NULL)); 
	//char jogada_rodada[30];
	//int letra_rodada, categoria_rodada;

	printf("Digite o número de jogadores (no mínimo 2 e no máximo 10): \n");
	scanf("%d", &numero_jogadores);
	validar_num_jogadores(&numero_jogadores); //VALIDAR QUANDO A ENTRADA FOR UMA LETRA
	Jogador participantes[numero_jogadores];
	double pontos[numero_jogadores];
	
	//int ordem[numero_jogadores], ordem_categoria[5];
	//double pontos[numero_jogadores];

	//ordem_rodada(ordem_categoria, 5);

	inic_pontos(pontos, numero_jogadores);

	jogadores_nomes(participantes, numero_jogadores);

	rodadas(numero_jogadores, participantes);

	return 0;
}



