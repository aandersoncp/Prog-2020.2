#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <ctype.h>
#include <unistd.h>
#include<string.h>

pthread_t thread_idA;
pthread_t thread_idB;

void * routine(void *arg){
	int r;
	int *contador = (int *)(arg);
	*contador = ((*contador)*2) + 2;
	while((*contador)--){
		printf("%d\n", *contador);
		arg = (void *)(contador);
		sleep(1);
	}
	r = pthread_cancel(thread_idB);
	pthread_exit(arg);
}

void * routine2(void *arg){	
	scanf("%s", (char *)(arg));
	pthread_exit(arg);
}

int main (int argc, char *argv[]){
	void * thread_resA;
	void * thread_resB;
	int rstatus, r, a = 2, ap1, ap2, fim = 1;
	char* jogada;
	
	rstatus = pthread_create (&thread_idA, NULL, routine, (void*)(&a));
	rstatus = pthread_create (&thread_idB, NULL, routine2, (void*)(jogada));

	while(fim){
		if(pthread_join(thread_idB, &thread_resB) == 0){
			printf("Entrei no fim de B\n");
			r = pthread_cancel(thread_idA);
			fim = 0;
		} else if(pthread_join(thread_idA, &thread_resA) == 0){
			r = pthread_cancel(thread_idB);
			fim = 0;
		}
	}
	return 0;
}