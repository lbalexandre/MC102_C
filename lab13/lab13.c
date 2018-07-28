

#include <stdio.h>

#define ALTURA_TABULEIRO 10
#define LARGURA_TABULEIRO 10

/* Funcao: atualiza_posicao
 *
 * Parametros:
 *     *l: apontador para a largura do bloco que ira cair
 *     *a: apontador para a altura do bloco que ira cair
 *     *x: apontador para a posicao horizontal inicial do bloco que ira cair
 *   desl: deslocamento horizontal a ser aplicado ao bloco (positivo para direita, negativo para a esquerda) 
 *    rot: 1 se deve rotacionar o bloco, 0 caso contrario 
 *
 * Retorno:
 *   NULL
 */
void atualiza_posicao(int *l, int *a, int *x, int desl, int rot){

	int aux, i;

	if(rot == 1){
		aux = *l;
		*l = *a;
		*a = aux;
	}
   	
	if(desl > 0){
		i = *x + *l;
		if(10 - i < desl)
			desl = 10 - i;

		*x = *x + desl;	
	}else{
		desl = desl*(-1);
		if(*x < desl)
			desl = *x;

		*x = *x - desl;				
	}	
}

/* Funcao: encontra_y
 *
 * Parametros:
 *    mat: matriz representando o tabuleiro 
 *      l: largura do bloco que ira cair
 *      x: posicao horizontal do bloco que ira cair
 *
 * Retorno:
 *   altura final y do canto inferior esquerdo do bloco apos
 *   este descer o maximo possivel
 */
int encontra_y(int mat[ALTURA_TABULEIRO][LARGURA_TABULEIRO], int l, int x){

	int i, j;

	for(i=9; i>=0; i--){
		for(j=x; j<x+l; j++){
			if(mat[i][j] == 1)
				return i+1;		
		}
	}

	return 0;			
}

/* Funcoes: posicao_final_valida
 *
 * Parametros:
 *      a: altura do bloco que caiu
 *      y: altura final do bloco que caiu
 *
 * Retorno:
 *   1 se o bloco naquela posicao estiver contido dentro do tabuleiro, ou 0 caso contrario.
 */
int posicao_final_valida(int a,  int y){

	if(y + a > 10)
		return 0;
	else
		return 1;
}

/* Funcoes: posiciona_bloco
 *
 * Parametros:
 *    mat: matriz do tabuleiro 
 *      l: largura do novo bloco
 *      a: altura do novo bloco
 *      x: posicao horizontal do novo bloco
 *      y: altura final do novo bloco
 *
 *      Deve preencher com 1s as novas posições ocupadas pelo bloco que caiu
 * Retorno:
 *   NULL
 */
void posiciona_bloco(int mat[ALTURA_TABULEIRO][LARGURA_TABULEIRO], int l, int a, int x, int y){
  
	int i, j;

	for(i=y; i<y+a; i++){
		for(j=x; j<x+l; j++)
			mat[i][j] = 1;		
	}
}

/* Funcoes: atualiza_matriz
 *
 * Parametros:
 *    mat: matriz do tabuleiro 
 *
 *         Deve remover as linhas totalmente preenchidas do tabuleiro copiando
 *         linhas posicionadas acima.
 * Retorno:
 *   retorna o numero de linhas totalmente preenchidas que foram removidas apos
 *   a atualizacao do tabuleiro.
 */
int atualiza_matriz(int mat[ALTURA_TABULEIRO][LARGURA_TABULEIRO]){
    
	int i, j, k, n, m;
	int linha = 0, pontos = 0;

	for(i=9; i>=0; i--){
		for(j=0; j<10; j++){
			if(mat[i][j] == 1)
				linha++;
		}

		if(linha == 10){
			pontos++;

			for(k=i; k<10; k++){
				for(n=0; n<10; n++)
					mat[k][n] = mat[k+1][n];
			}
		
			for(m=0; m<10; m++)
				mat[9][m] = 0;	
		}
		linha = 0;	
	}

	return pontos;
}
