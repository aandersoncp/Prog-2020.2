#include <stdio.h>

void extenso(int x){
	int a, b, c;
	char unidades[9][7] = {"um", "dois", "tres", "quatro", "cinco", "seis", "sete", "oito", "nove"};
	char dezenas_1[9][10] = {"onze", "doze", "treze", "catorze", "quinze", "dezesseis", "dezessete", "dezoito", "dezenove"};
	char dezenas_2[9][10] = {"dez", "vinte", "trinta", "quarenta", "cinquenta", "sessenta", "setenta", "oitenta", "noventa"};
	char centenas[10][13] = {"cem", "cento", "duzentos", "trezentos", "quatrocentos", "quinhentos", "seiscentos", "setessentos", "oitocentos", "novecentos"};
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
		printf("c = %d, b = %d, a = %d\n", c, b, a);
		if(a == 0 && b == 0 && c == 1){
			printf("%s\n", centenas[0]);
		} else if(a == 0){
			printf("%s e %s\n", centenas[c], dezenas_2[b - 1]);
		} else if(b == 0){
			printf("%s e %s\n", centenas[c], unidades[a - 1]);
		} else if(b == 1){
			printf("%s e %s\n", centenas[c], dezenas_1[b - 1]);
		} else{
			printf("%s e %s e %s\n", centenas[c], dezenas_2[b - 1], unidades[a - 1]);
		} 
	}
}

int main(){
	int x;
	printf("Digite um número inteiro de 1 até 999: \n");
	scanf("%d", &x);
	while(x > 999 || x < 1){
		printf("Digite um número inteiro de 1 até 999: \n");
		scanf("%d", &x);
	}
	extenso(x);
}


