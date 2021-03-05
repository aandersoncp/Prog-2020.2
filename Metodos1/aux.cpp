#include <iostream>
#include <math.h>

using namespace std;
#define DIM 10

void substituicaoSucessivas(int n, float A[][DIM], float b[], float x[]){
	int soma;
	x[0] = b[0]/A[0][0];
	for(int i = 1; i < n; i++){
		soma = 0;
		for(int j = 0; j < i; j++){
			soma = soma + A[i][j]*x[j];
		}
		x[i] = (b[i] - soma)/A[i][i];
	}	
}

void substituicaoRetroativas(int n, float A[][DIM], float b[], float x[]){
	int soma;
	x[n - 1] = b[n - 1]/A[n - 1][n - 1];
	for(int i = (n - 2); i >= 0; i--){
		soma = 0;
		for(int j = i + 1; j < n; j++){
			soma = soma + A[i][j]*x[j];
		}
		x[i] = (b[i] - soma)/A[i][i];
	}	
}


void eliminacaoGaussiana(int n, float A[][DIM], float b[]){
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
}

void gaussPivoteamentoParcial(){
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
}



//GAUSS COM PIVOTEAMENTO PARCIAL
void gaussComPivoteamenteParcial(){
	double max, aux, m, aux3;
	int p, index, vetor_aux[n], aux2;

	for(int i = 0; i < n; i++){
		vetor_aux[i] = i;
	}

	for(int j = 0; j < n - 1; j++){ // j COLUNA
		max = A[j][j];
		index = j;
		for(p = j; p < n; p++){ //p LINHA 
			if(A[p][j] > max){ // abs(A[p][j]) > max
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
			U[i][j] = m;
			A[i][j] = 0; //// A[i][j] = m;
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
}


/////////////DETERMINANTE///////////////////////
void determinante(){
float det = 1;
	for(int k = 0; k < n; k++){
		for(int j = k + 1; j < n; j++){
			A[k][j] = A[k][j]/A[k][k];
		}
		b[k] = b[k]/A[k][k];
		det *= A[k][k]; 
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
	printf("det(A) = %f\n\n", det);

	//////// MOSTRAR ///////////
	for(int linhas = 0; linhas < n; linhas++){
		for(int colunas = 0; colunas < n; colunas++){
			printf("%.2f ", A[linhas][colunas]);
		}
		printf("\n");
	}
	printf("\n");
}



///////////////// INVERSA COM GAUSS JORDAN ///////////////////////////////////
void inversaGaussJordan(){
float I[DIM][DIM];
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(i == j){
				I[i][j] = 1;
			} else{
				I[i][j] = 0;
			}
		}
	}
	printf("IDENTIDADE:\n");
	for(int linhas = 0; linhas < n; linhas++){
		for(int colunas = 0; colunas < n; colunas++){
			printf("%.2f ", I[linhas][colunas]);
		}
		printf("\n");
	}
	printf("\n");

	printf("A:\n");
	for(int linhas = 0; linhas < n; linhas++){
		for(int colunas = 0; colunas < n; colunas++){
			printf("%.2f ", A[linhas][colunas]);
		}
		printf("\n");
	}
	printf("\n");

	/////////////////////////////
	for(int k = 0; k < n; k++){
		for(int j = k + 1; j < n; j++){
			A[k][j] = A[k][j]/A[k][k];
		}
		for(int j = 0; j < n; j++){
			I[k][j] = I[k][j]/A[k][k];
		}
		A[k][k] = 1;
		
		float multi;
		for(int i = 0; i < n; i++){
			if(i != k){
				for(int j = k + 1; j < n; j++){
					multi = A[i][k];
					A[i][j] = A[i][j] - A[i][k]*A[k][j];
				}
				for(int h = 0; h < n; h++){
					if(k < n - 1){
						I[i][h] = I[i][h] - multi*I[k][h];
					} else {
						I[i][h] = I[i][h] - A[i][k]*I[k][h];
					}
				}
				A[i][k] = 0;
			}
		}
	}

	printf("IDENTIDADE:\n");
	//////// MOSTRAR ///////////
	for(int linhas = 0; linhas < n; linhas++){
		for(int colunas = 0; colunas < n; colunas++){
			printf("%.2f ", I[linhas][colunas]);
		}
		printf("\n");
	}
	printf("\n");


	printf("A:\n");
	for(int linhas = 0; linhas < n; linhas++){
		for(int colunas = 0; colunas < n; colunas++){
			printf("%.2f ", A[linhas][colunas]);
		}
		printf("\n");
	}
	printf("\n");
}


///////////FATORAÇÃO LU NORMAL///////////////////
void fatoracaoLUNormal(){
float L[DIM][DIM], U[DIM][DIM];

	for(int linha = 0; linha < n; linha++){
		for(int coluna = 0; coluna < n; coluna++){
			U[linha][coluna] = A[linha][coluna];
		}
	}

	for(int linha = 0; linha < n; linha++){
		for(int coluna = 0; coluna < n; coluna++){
			if(linha > coluna){
				L[linha][coluna] = A[linha][coluna]/A[coluna][coluna];
			} else if(linha == coluna){
				L[linha][coluna] = 1;
			} else{
				L[linha][coluna] = 0;
			}
		}
	}

	float m;
	for(int k = 0; k < n; k++){
		for(int i = k + 1; i < n; i++){
			m = -U[i][k]/U[k][k];
			U[i][k] = 0;
			for(int j = k + 1; j < n; j++){
				U[i][j] = U[i][j] + m*U[k][j];
			}
		b[i] = b[i] + m*b[k]; 
		}
	}


	for(int linhas = 0; linhas < n; linhas++){
		for(int colunas = 0; colunas < n; colunas++){
			printf("%.2f ", L[linhas][colunas]);
		}
		printf("\n");
	}
	printf("\n");


	for(int linhas = 0; linhas < n; linhas++){
		for(int colunas = 0; colunas < n; colunas++){
			printf("%.2f ", U[linhas][colunas]);
		}
		printf("\n");
	}
	printf("\n");
}



int main(){ 
	int n = 3;
	double A[DIM][DIM], b[n];
	double x[n];

	A[0][0] = 1;
	A[0][1] = -3;
	A[0][2] = 2;

	A[1][0] = -2;
	A[1][1] = 8;
	A[1][2] = -1;

	A[2][0] = 4;
	A[2][1] = -6;
	A[2][2] = 5;

	b[0] = 11;
	b[1] = -15;
	b[2] = 29;

	float L[DIM][DIM], U[DIM][DIM];

	for(int linha = 0; linha < n; linha++){
		for(int coluna = 0; coluna < n; coluna++){
			U[linha][coluna] = A[linha][coluna];
		}
	}

	for(int linha = 0; linha < n; linha++){
		for(int coluna = 0; coluna < n; coluna++){
			if(linha > coluna){
				L[linha][coluna] = A[linha][coluna]/A[coluna][coluna];
			} else if(linha == coluna){
				L[linha][coluna] = 1;
			} else{
				L[linha][coluna] = 0;
			}
		}
	}

	float m;
	for(int k = 0; k < n; k++){
		for(int i = k + 1; i < n; i++){
			m = -U[i][k]/U[k][k];
			U[i][k] = 0;
			for(int j = k + 1; j < n; j++){
				U[i][j] = U[i][j] + m*U[k][j];
			}
		b[i] = b[i] + m*b[k]; 
		}
	}


	for(int linhas = 0; linhas < n; linhas++){
		for(int colunas = 0; colunas < n; colunas++){
			printf("%.2f ", L[linhas][colunas]);
		}
		printf("\n");
	}
	printf("\n");


	for(int linhas = 0; linhas < n; linhas++){
		for(int colunas = 0; colunas < n; colunas++){
			printf("%.2f ", U[linhas][colunas]);
		}
		printf("\n");
	}
	printf("\n");

	return 0;
}

///////FATORAÇÃO LU COM PIVOTEAMENTO PARCIAL //////
void fatoracaoLUPivoteamentoParcial(){
	float L[DIM][DIM], U[DIM][DIM];

	for(int linha = 0; linha < n; linha++){
		for(int coluna = 0; coluna < n; coluna++){
			U[linha][coluna] = A[linha][coluna];
		}
	}

	//GAUSS COM PIVOTEAMENTO PARCIAL
	double max, aux, m, aux3;
	int p, index, vetor_aux[n], aux2;

	for(int i = 0; i < n; i++){
		vetor_aux[i] = i;
	}

	for(int j = 0; j < n - 1; j++){ // j COLUNA
		max = U[j][j];
		index = j;
		//PROCURAR O PIVO
		for(p = j; p < n; p++){ //p LINHA 
			if(abs(U[p][j]) > max){
				max = U[p][j];
				index = p;
			}
		}
		if(max == 0){
			return 0;
		}

		if(index != j){
			for(int s = 0; s < n; s++){ //TROCANDO A LINHA[J] PELA LINHA[INDEX]
				aux = U[index][s];
				U[index][s] = U[j][s];
				U[j][s] = aux;

				aux = L[index][s];
				L[index][s] = L[j][s];
				L[j][s] = aux;
			}
			//TROCANDO A B[J] PELO B[INDEX]
			aux3 = b[index];
			b[index] = b[j];
			b[j] = aux3;


			//GUARDANDO AS ALTERAÇÕES
			aux2 = vetor_aux[index];
			vetor_aux[index] = vetor_aux[j];
			vetor_aux[j] = aux2;
		}

		//PARTE DA ELIMINAÇÃO DE GAUSS
		for(int i = j + 1; i < n; i++){ //PARA CADA LINHA
			m = (U[i][j]/U[j][j]);
			L[i][j] = m;
			U[i][j] = 0;
			for(int k = j + 1; k < n; k++){
				U[i][k] = U[i][k] - m*U[j][k];
			}
			b[i] = b[i] - m*b[j];
		} 
	}

	printf("b:\n");
	for(int colunas = 0; colunas < n; colunas++){
		printf("%f ", b[colunas]);
	}
	printf("\n\n");


for(int linha = 0; linha < n; linha++){
		for(int coluna = 0; coluna < n; coluna++){
			if(linha == coluna){
				L[linha][coluna] = 1;
			} else if(coluna > linha){
				L[linha][coluna] = 0;
			}
		}
	}

	printf("L:\n");
	for(int linhas = 0; linhas < n; linhas++){
		for(int colunas = 0; colunas < n; colunas++){
			printf("%.3f ", L[linhas][colunas]);
		}
		printf("\n");
	}
	printf("\n");

	printf("U:\n");
	for(int linhas = 0; linhas < n; linhas++){
		for(int colunas = 0; colunas < n; colunas++){
			printf("%.3f ", U[linhas][colunas]);
		}
		printf("\n");
	}
	printf("\n");
}

double calcula_norma(int n, double x[], double v[]){
	double normaNum = 0, normaDen = 0, t;
	for(int i = 0; i < n; i++){
		t = abs(v[i] - x[i]);
		if(t > normaNum){
			normaNum = t;
		} 
		if(abs(v[i]) > normaDen){
			normaDen = abs(v[i]);
		}
		x[i] = v[i];
	}
	return (normaNum/normaDen);
}

void gaussJacobi(){
	int n = 3, k = 0, iterMax = 10;
	double A[DIM][DIM], b[n], r, soma, norma;
	double x[n], e = 0.5, v[n];
	
	for(int i = 0; i < n; i++){
		r = 1/A[i][i];
		for(int j = 0; j < n; j++){
			if(i != j){
				A[i][j] = A[i][j]*r;
			}
		}
		b[i] = b[i]*r;
		x[i] = b[i];
	}

	do{
		k++;
		for(int i = 0; i < n; i++){
			soma = 0;
			for(int j = 0; j < n; j++){
				if(i != j){
					soma = soma + A[i][j]*x[j];
				}
			}
			v[i] = b[i] - soma;
		}
		norma = calcula_norma(n, x, v);
		printf("k = %d\n", k);
		printf("x = ");
		for(int cont = 0; cont < n; cont++){
			printf("% lf",x[cont]);
		}
		printf("\nNorma = %lf\n", norma);
	} while(norma >= e && k < iterMax);
	
	printf("x = ");
	for(int cont = 0; cont < n; cont++){
		printf("% lf,", x[cont]);
	}
	printf("\n");

}