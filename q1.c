#include <stdio.h>

void extenso(int x){
	int a, b, c;
	char unidades[9][7] = {"Um", "Dois", "Três", "Quatro", "Cinco", "Seis", "Sete", "Oito", "Nove"};
	char dezenas_1[9][10] = {"Onze", "Doze", "Treze", "Catorze", "Quinze", "Dezesseis", "Dezessete", "Dezoito", "Dezenove"};
	char dezenas_2[9][10] = {"Dez", "Vinte", "Trinta", "Quarenta", "Cinquenta", "Sessenta", "Setenta", "Oitenta", "Noventa"};
	char centenas[10][13] = {"Cem", "Cento", "Duzentos", "Trezentos", "Quatrocentos", "Quinhentos", "Seiscentos", "Setessentos", "Oitocentos", "Novecentos"};
	if(x < 10){
		printf("%s\n", unidades[x - 1]);
	} else if(x < 20){
		printf("%s\n", dezenas_1[(x % 10)  - 1]);
	} else if(x < 100){
		a = x % 10;
		b = ((x - a)/10) % 10;
		if(a == 0){
			printf("%s\n", dezenas_2[b - 1]);
		} else {
			printf("%s e %s\n", dezenas_2[b - 1], unidades[a - 1]);
		}
	} else {
		a = x % 10;
		b = ((x - a) / 10) % 10;
		c = ((((x - a) / 10) - b)/10) % 10;
		//printf("c = %d, b = %d, a = %d\n", c, b, a);
		if(a == 0 && b == 0 && c == 1){
			printf("%s\n", centenas[0]);
		} else if(a == 0){
			printf("%s e %s\n", centenas[c], dezenas_2[b - 1]);
		} else if(b == 0){
			printf("%s e %s\n", centenas[c], unidades[a - 1]);
		} else if(b == 1){
			printf("%s e %s\n", centenas[c], dezenas_1[a - 1]);
		} else{
			printf("%s e %s e %s\n", centenas[c], dezenas_2[b - 1], unidades[a - 1]);
		} 
	}
}

int converter(char* numero){
	int x = 0, i = 0;
	while(numero[i] != '\n' && i < 4){
		if(numero[i] == '0'){
			x = x*10;
		} else if(numero[i] == '1'){
			x = x*10 + 1;
		} else if(numero[i] == '2'){
			x = x*10 + 2;
		} else if(numero[i] == '3'){
			x = x*10 + 3;
		} else if(numero[i] == '4'){
			x = x*10 + 4;
		} else if(numero[i] == '5'){
			x = x*10 + 5;
		} else if(numero[i] == '6'){
			x = x*10 + 6;
		} else if(numero[i] == '7'){
			x = x*10 + 7;
		} else if(numero[i] == '8'){
			x = x*10 + 8;
		} else if(numero[i] == '9'){
			x = x*10 + 9;
		} else{
			x = x;
		}
		i++; 
	}
	//printf("resultado: %d\n", x);
	return x;
}

int main(){
	int x;
	char num[5];
	FILE *arq;
	arq = fopen("numeros.txt","rt");
	if (arq == NULL) {
		printf("Não foi possível abrir o arquivo.\n");
		return 0;
	}
	while(fgets(num, 5, arq) != NULL){
		//printf("numero: %s\n", num);
		x = converter(num);
		if(x > 0 && x < 1000){
			extenso(x);
		} else {
			printf("Número fora do intervalo considerado.\n");
		}
	}
	return 0;
}


/*
int main(){
	int x;
	FILE *arq;
	arq = fopen(“numeros.txt”,”rt”);
	if (arq == NULL) {
		printf(“Não foi possível abrir o arquivo.\n”);
		return EXIT_FAILURE;
	}
	printf("Digite um número inteiro de 1 até 999: \n");
	scanf("%d", &x);
	while(x > 999 || x < 1){
		printf("Digite um número inteiro de 1 até 999: \n");
		scanf("%d", &x);
	}
	extenso(x);
}


*/

