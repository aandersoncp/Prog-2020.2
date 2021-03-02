#include <iostream>
#include <math.h>

using namespace std;
#define DIM 10

/*void substituicaoSucessivas(int n, float A[][DIM], float b[], float x[]){
	int soma;
	x[0] = b[0]/A[0][0];
	for(int i = 1; i < n; i++){
		soma = 0;
		for(int j = 0; j < i; j++){
			soma = soma + A[i][j]*x[j];
		}
		x[i] = (b[i] - soma)/A[i][i];
	}	
}*/

/*void substituicaoRetroativas(int n, float A[][DIM], float b[], float x[]){
	int soma;
	x[n - 1] = b[n - 1]/A[n - 1][n - 1];
	for(int i = (n - 2); i >= 0; i--){
		soma = 0;
		for(int j = i + 1; j < n; j++){
			soma = soma + A[i][j]*x[j];
		}
		x[i] = (b[i] - soma)/A[i][i];
	}	
}*/


/*void eliminacaoGaussiana(int n, float A[][DIM], float b[]){
	float m;
	for(int k = 0; k < n; k++){
		for(int i = k + 1; i < n; i++){
			m = -A[i][k]/A[k][k];
			A[i][k] = 0;
			for(int j = k + 1; j < n; j++){
				A[i][j] = A[i][j] + m*A[k][j];
			}
		b[i] = b[i] + m*b[k]; 
		}
	}
}*/

/*void gaussPivoteamentoParcial(){
	double max, aux, m, aux3;
	int p, index, vetor_aux[n], aux2;

	for(int i = 0; i < n; i++){
		vetor_aux[i] = i;
	}

	for(int j = 0; j < n - 1; j++){ // j COLUNA
		max = A[j][j];
		index = j;
		for(p = j; p < n; p++){ //p LINHA 
			if(A[p][j] > max){
				max = A[p][j];
				index = p;
			}
		}
		if(index != j){
			for(int s = 0; s < n; s++){
				aux = A[index][s];
				A[index][s] = A[j][s];
				A[j][s] = aux;
			}
			aux3 = b[index];
			b[index] = b[j];
			b[j] = aux3;

			aux2 = vetor_aux[index];
			vetor_aux[index] = vetor_aux[j];
			vetor_aux[j] = aux2;
		}

		for(int i = j + 1; i < n; i++){
			m = -(A[i][j]/A[j][j]);
			A[i][j] = 0;
			for(int k = j + 1; k < n; k++){
				A[i][k] = A[i][k] + m*A[j][k];
			}
			b[i] = b[i] + m*b[j];
		} 
	}

	substituicaoRetroativas();
}*/

/*

//GAUSS COM PIVOTEAMENTO PARCIAL
	double max, aux, m, aux3;
	int p, index, vetor_aux[n], aux2;

	for(int i = 0; i < n; i++){
		vetor_aux[i] = i;
	}

	for(int j = 0; j < n - 1; j++){ // j COLUNA
		max = A[j][j];
		index = j;
		for(p = j; p < n; p++){ //p LINHA 
			if(A[p][j] > max){
				max = A[p][j];
				index = p;
			}
		}
		if(index != j){
			for(int s = 0; s < n; s++){
				aux = A[index][s];
				A[index][s] = A[j][s];
				A[j][s] = aux;
			}
			aux3 = b[index];
			b[index] = b[j];
			b[j] = aux3;

			aux2 = vetor_aux[index];
			vetor_aux[index] = vetor_aux[j];
			vetor_aux[j] = aux2;
		}

		for(int i = j + 1; i < n; i++){
			m = -(A[i][j]/A[j][j]);
			A[i][j] = 0;
			for(int k = j + 1; k < n; k++){
				A[i][k] = A[i][k] + m*A[j][k];
			}
			b[i] = b[i] + m*b[j];
		} 
	}

	for(int colunas = 0; colunas < n; colunas++){
		printf("%f ", b[colunas]);
	}
	printf("\n");

*/

int main(){ 
	int n = 3;
	double A[DIM][DIM], b[n];
	double x[n];

	A[0][0] = 1;
	A[0][1] = 2;
	A[0][2] = 3;
	//A[0][3] = 1;

	A[1][0] = 3;
	A[1][1] = -4;
	A[1][2] = 1;
	//A[1][3] = -4;

	A[2][0] = 1;
	A[2][1] = 2;
	A[2][2] = 7;
	//A[2][3] = 5;

	//A[3][0] = 1;
	//A[3][1] = 2;
	//A[3][2] = ;
	//A[3][3] = 2;

	b[0] = 1;
	b[1] = 2;
	b[2] = 3;
	//b[3] = 8;

	for(int linhas = 0; linhas < n; linhas++){
		for(int colunas = 0; colunas < n; colunas++){
			printf("%.2f ", A[linhas][colunas]);
		}
		printf("\n");
	}
	printf("\n");


	//eliminacaoGaussiana
	/*float m;
	for(int k = 0; k < n; k++){ //colunas
		for(int i = k + 1; i < n; i++){ // linhas
			m = -A[i][k]/A[k][k];
			A[i][k] = 0;
			for(int j = k + 1; j < n; j++){
				A[i][j] = A[i][j] + m*A[k][j];
			}
		b[i] = b[i] + m*b[k]; 
		}
	}*/

	//substituicaoRetroativas
	/*float soma;
	x[n - 1] = b[n - 1]/A[n - 1][n - 1];
	for(int i = (n - 2); i >= 0; i--){
		soma = 0;
		for(int j = i + 1; j < n; j++){
			soma = soma + A[i][j]*x[j];
		}
		x[i] = (b[i] - soma)/A[i][i];
	}	

	for(int i = 0; i < n; i++){
		printf("x[%d] = %f\n", i, x[i]);
	}*/

	/////////////////////////////
	float multi = 1;
	for(int k = 0; k < n; k++){
		for(int j = k + 1; j < n; j++){
			A[k][j] = A[k][j]/A[k][k];
		}
		b[k] = b[k]/A[k][k];
		multi *= A[k][k]; 
		A[k][k] = 1;
		for(int i = 0; i < n; i++){
			if(i != k){
				for(int j = k + 1; j < n; j++){
					A[i][j] = A[i][j] - A[i][k]*A[k][j];
				}
				b[i] = b[i] - A[i][k]*b[k];
				A[i][k] = 0;
			}
		}
	}
	//x = b; //x é um vetor saída
	printf("multi = %f\n\n", multi);

	//////// MOSTRAR ///////////
	for(int linhas = 0; linhas < n; linhas++){
		for(int colunas = 0; colunas < n; colunas++){
			printf("%.2f ", A[linhas][colunas]);
		}
		printf("\n");
	}
	printf("\n");
	//////// MOSTRAR ///////////

	/*float soma;
	x[n - 1] = b[n - 1]/A[n - 1][n - 1];
	for(int i = (n - 2); i >= 0; i--){
		soma = 0;
		for(int j = i + 1; j < n; j++){
			soma = soma + A[i][j]*x[j];
		}
		x[i] = (b[i] - soma)/A[i][i];
	}	*/

	for(int i = 0; i < n; i++){
		printf("b[%d] = %f\n", i, b[i]);
	}

	return 0;
}
