
#include <stdio.h>

#define MAX 9

/*
 * Funcao: print_sudoku
 * Essa funcao ja esta implementada no arquivo lab18_main.c
 * A funcao imprime o tabuleiro atual do sudoku de forma animada, isto e,
 * imprime o tabuleiro e espera 0.1s antes de fazer outra modificacao.
 * Voce deve chamar essa funcao a cada modificacao na matriz resposta, assim
 * voce tera uma animacao similar a apresentada no enunciado.
 * Essa funcao nao tem efeito na execucao no Susy, logo nao ha necessidade de
 * remover as chamadas para submissao.
 */
void print_sudoku(int resposta[MAX][MAX]);

// Verifica se um dado numero pode ser incluido em uma posicao
int verificacao(int resposta[MAX][MAX], int linha, int coluna, int numero){
	
	int i, j;
	int l, c;
	
	// Verifica se o numero ja esta presente na coluna
	for(j=0; j<MAX; j++){
		if(resposta[linha][j] == numero)
			return 0;
	}
	
	// Verifica se o numero ja esta presenta na linha
	for(i=0; i<MAX; i++){
		if(resposta[i][coluna] == numero)
			return 0;
	}

	// Verifica se o numero ja esta presente no quadrante
	l = (linha / 3) * 3;
	c = (coluna / 3 ) * 3;

	for(i=l; i<l+3; i++){
		for(j=c; j<c+3; j++){
			if(resposta[i][j] == numero)
				return 0;
		}
	}
	
	return 1;	
}

// Gera a solucao, se houve, do Sudoku
int resolucao(int resposta[MAX][MAX], int i, int j){

	int num, teste;
	int linha, coluna;

    	coluna = j; 
	linha = i;
 
	if(i == 9) 
		return 1;
 
	if(coluna < 8)
		coluna++;
	else{
       		linha++;
        	coluna = 0;
	}
 
	if(resposta[i][j]){
		teste = resolucao(resposta, linha, coluna);
		return teste;
	}else{
       		for(num=1; num<=9; num++){
			if(verificacao(resposta, i, j, num)){
				resposta[i][j] = num;
               
                		if(resolucao(resposta, linha, coluna)) 
					return 1;

                		resposta[i][j] = 0;
			}
		}
	}

	return 0;
}
			
/*
 * Funcao: resolve
 * Resolve o Sudoku da matriz resposta.
 * Retorna 1 se encontrar uma resposta, 0 caso contrario
 */
int resolve(int resposta[MAX][MAX]){

	int i;
	
	// Chamada da funcao que gerara a solucao
 	i = resolucao(resposta, 0, 0);

	if(i)	 
		print_sudoku(resposta);
			
	return 1;
}
