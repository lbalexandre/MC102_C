
/* Programa que determina o estado de um populacao que se encontra em um apocalpse zumbi. A entrada consiste nas dimensoes
de uma matriz que representa uma determinada populacao inicial e o numedo de dias que serao analisados. A saida consite
no estado da populacao em todos os dias ate final determinado */

#include <stdio.h>

int main(){

	int matriz[100][100], matrizR[100][100];
	int linhas = 0, colunas = 0, dias = 0;
	int vetor[8] = {0};
	int i=0, j=0, k=0, n=0, a=0, b=0, d=0, e=0, m=0;
	

	// Entrada dimensao da matriz da populacao inicial
	scanf("%d %d", &linhas, &colunas);

	// Entrada da quantidade de dias que serao analisados
	scanf("%d", &dias);

	linhas = linhas + 2;
	colunas = colunas + 2;

	// Envoltando a matriz com zeros
	for(j=0; j<colunas; j++)
        	matriz[0][j] = 0;
    
	for(j=0; j<colunas; j++)
 		matriz[linhas-1][j] = 0;
    
	for(i=0; i<colunas; i++)
        	matriz[i][0] = 0;
    
	for(i=0; i<colunas; i++)
		matriz[i][colunas-1] = 0;


	// Envoltando a matriz resultado com zeros
	for(j=0; j<colunas; j++)
        	matrizR[0][j] = 0;
    
	for(j=0; j<colunas; j++)
 		matrizR[linhas-1][j] = 0;
    
	for(i=0; i<colunas; i++)
        	matrizR[i][0] = 0;
    
	for(i=0; i<colunas; i++)
		matrizR[i][colunas-1] = 0;

	// Entrada dos seres, sendo 0 vazio, 1 humanos e 2 zumbi
	for(i=1; i<linhas-1; i++){
        	for(j=1; j<colunas-1; j++)
 			scanf("%d", &matriz[i][j]);
	}

	// Impressao da matriz da populacao inicial
	printf("iteracao 0\n");
	for(i=1; i<linhas-1; i++){
		for(j=1; j<colunas-1; j++){
			printf("%d", matriz[i][j]);
		}
			printf("\n");
        }	

	// Realizacao das intecacoes na populacao
	for(m=1; m<=dias; m++){
		for(i=1; i<linhas-1; i++){
        		for(j=1; j<colunas-1; j++){
	
				// E necessario analisar cada vizinho de um individuo 
				vetor[0] = matriz[i-1][j-1];
				vetor[1] = matriz[i-1][j];
				vetor[2] = matriz[i-1][j+1];
				vetor[3] = matriz[i][j-1];
				vetor[4] = matriz[i][j+1];
				vetor[5] = matriz[i+1][j-1];
				vetor[6] = matriz[i+1][j];
				vetor[7] = matriz[i+1][j+1];

				// Caso o lugar esteja vazio
				n=0;
				if(matriz[i][j] == 0){
					for(k=0; k<8; k++){
						if(vetor[k] == 1)
							n++;
					}
					if(n == 2){
						matrizR[i][j]  = 1;
					}else{
						matrizR[i][j] = matriz[i][j];
					}
				// Caso o local contenha um humano
				}else if(matriz[i][j] == 1){
				
					for(k=0; k<8; k++){
						if(vetor[k] == 2)
							n++;
					}

					if(n != 0){
						matrizR[i][j]  = 2;
					}else{
						matrizR[i][j] = matriz[i][j];
					}
				// Caso o local contenha um zumbi
				}else if(matriz[i][j] == 2){
					
					for(k=0; k<8; k++){
						if(vetor[k] == 1)
							n++;
					}
					if(n == 1)
						matrizR[i][j] = matriz[i][j];
					if(n == 0 || n >=2)
						matrizR[i][j] = 0;
				}		
			}
		}	
	
		// Impresao do estado da populacao apos o dia de interacao
		printf("iteracao %d\n", m);
		for(a=1; a<linhas-1; a++){
			for(b=1; b<colunas-1; b++){
				printf("%d", matrizR[a][b]);
			}
			printf("\n");
        	}	

		// A nova populacao a ser analisada recebe a populacao do dia anterior
		for(d=1; d<linhas-1; d++){
			for(e=1; e<colunas-1; e++){
				matriz[d][e] = matrizR[d][e];
			}
		}
	}				
	    
    return 0;
}
