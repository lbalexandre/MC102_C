
#include <stdio.h>

#define MAX 20
#define MONSTROS 151

/* Funcao: busca
 * A funcao deve encontrar a posição (i,j) do jogador no tabuleiro.
 * O jogador é representado pelo valor -1.
 * O retorno da posicao se da pelo vetor parametro pos.
 *
 *
 * Parametros:
 *    tab: tabuleiro
 *    pos: posicao do jogador no tabuleiro
 *
 * Retorno:
 *   Em pos[0] deve ser setado a linha i onde esta o jogador.
 *   Em pos[1] deve ser setado a coluna j onde esta o jogador.
 */
void busca(int tab[MAX][MAX], int pos[2]){
  
	int i, j;

	for(i=0; i<MAX; i++){
		for(j=0; j<MAX; j++){
			if(tab[i][j] == -1){
				pos[0] = i;
				pos[1] = j;	
			}
		}
	}	
}

/* Funcao: visiveis
 * Retorna os monstros visiveis nas 8 posições adjacentes em ordem.
 * A posição 0 representa o canto superior esquerdo e a posição 7 o canto
 * inferior direito.
 * 0 1 2
 * 3 J 4
 * 5 6 7
 * As posições devem ter o identificador da especie do monstro presente ou zero se a
 * posição não tiver um monstro.
 *
 * Parametros:
 *    tab: tabuleiro
 *      v: Identificadores das posições adjacentes
 *
 * Retorno:
 *    Para cada posicao v[i], onde i=0,1,..7, deve ser setado
 *    o identificador da especie do monstro naquela posição ou 0 se a posicao
 *    estiver vazia.
 */
void visiveis(int tab[MAX][MAX], int v[8]){

	int i, j, P[2] = {0};
  	
	busca(tab, P); 

	i=P[0];
	j=P[1];

	if(i > 0 && j > 0 )
		v[0] = tab[i-1][j-1];
	if(i > 0 )
		v[1] = tab[i-1][j];
	if(i > 0 && j < 19 )
		v[2] = tab[i-1][j+1];
	if(j > 0)
		v[3] = tab[i][j-1];
	if(j < 19)
		v[4] = tab[i][j+1];
	if(i < 19 && j > 0)
		v[5] = tab[i+1][j-1];
	if(i < 19)
		v[6] = tab[i+1][j];
	if(i < 19 && j < 19)
		v[7] = tab[i+1][j+1];	
}

/* Funcao: proximos
 * Retorna quais tipos de monstros estão presentes nas 16 posições proximas ao
 * jogador mas não adjacentes a ele.
 * O valor de p[i] deve ser setado para 1 se existir ao menos uma ocorrência do monstro de
 * identificador i+1 em alguma das 16 posições proximas, ou 0 caso contrário.
 *
 * Parametros:
 *    tab: tabuleiro
 *      p: Monstros proximos
 *
 * Retorno:
 *    Note que o parametro p eh um vetor de tamanho igual ao numero de especies de monstros, ou seja 151.
 *    Para cada posição i, p[i] deve ser setado com 1 se um monstro de especie (i+1) esta proximo
 *    e 0 caso contrario.
 */
void proximos(int tab[MAX][MAX], int p[MONSTROS]) {
  
	int i, j, esp=0, P[2] = {0};
	
	busca(tab, P); 

	i=P[0];
	j=P[1];

	if(i > 1 && j > 1){
		if(tab[i-2][j-2]){
			esp = tab[i-2][j-2];
			p[esp-1] = 1;
		}
	}
	if(i < 18 && j > 1){
		if(tab[i+2][j-2]){
			esp = tab[i+2][j-2];
			p[esp-1] = 1;
		}
	}
	if(i > 1 && j < 18){
		if(tab[i-2][j+2]){
			esp = tab[i-2][j+2];
			p[esp-1] = 1;
		}
	}
	if(i < 18 && j < 18){
		if(tab[i+2][j+2]){
			esp = tab[i+2][j+2];
			p[esp-1] = 1;
		}
	}
	if(i > 0 && j > 1 ){
		if(tab[i-1][j-2]){
			esp = tab[i-1][j-2];
			p[esp-1] = 1;
		}
	}

	if(j > 1 ){
		if(tab[i][j-2]){
			esp = tab[i][j-2];
			p[esp-1] = 1;
		}
	}
	if(i < 19 && j > 1){
		if(tab[i+1][j-2]){
			esp = tab[i+1][j-2];
			p[esp-1] = 1;
		}
	}
	if(i > 1 && j > 0 ){
		if(tab[i-2][j-1]){
			esp = tab[i-2][j-1];
			p[esp-1] = 1;
		}
	}
	if(i > 1){
		if(tab[i-2][j]){
			esp = tab[i-2][j];
			p[esp-1] = 1;
		}
	}
	if(i > 1 && j < 19){
		if(tab[i-2][j+1]){
			esp = tab[i-2][j+1];
			p[esp-1] = 1;
		}
	}
	if(i < 18 && j > 0){
		if(tab[i+2][j-1]){
			esp = tab[i+2][j-1];
			p[esp-1] = 1;
		}
	}
	if(i < 18){
		if(tab[i+2][j]){
			esp = tab[i+2][j];
			p[esp-1] = 1;
		}
	}
	if(i < 18 && j < 19){
		if(tab[i+2][j+1]){
			esp = tab[i+2][j+1];
			p[esp-1] = 1;
		}
	}
	if(i > 0 && j < 18 ){
		if(tab[i-1][j+2]){
			esp = tab[i-1][j+2];
			p[esp-1] = 1;
		}
	}
	if(j < 18){
		if(tab[i][j+2]){
			esp = tab[i][j+2];
			p[esp-1] = 1;
		}
	}
	if(i < 19 && j < 18){
		if(tab[i+1][j+2]){
			esp = tab[i+1][j+2];
			p[esp-1] = 1;
		}
	}
}

/* Funcao: movimenta
 * Movimenta o jogador, que é representado no tabuleiro pelo valor -1.
 * O jogador deve sempre permanecer dentro do tabuleiro.
 *
 * Parametros:
 *    tab: tabuleiro
 *    desloca: contem o deslocamento que deve ser aplicado ao jogador.
 *             desloca[1] contem o deslocamento em colunas (-1, 0, ou 1)
 *             desloca[0] contem o deslocamento em linhas (-1, 0, ou 1)
 *
 * Retorno:
 *   Especie do monstro encontrado na nova posicao do jogador
 *   ou 0 se nao houver monstro nesta posicao.
 */
int movimenta(int tab[MAX][MAX], int desloca[2]){

	int i, j, especie=0, P[2] = {0};

	busca(tab, P); 

	i=P[0];
	j=P[1];

	if(desloca[0] == -1){
		if(i > 0){
			especie = tab[i-1][j];
			tab[i-1][j] = -1;
			tab[i][j] = 0;
		}
	}else if(desloca[0] == 1){
		if(i < 19){
			especie = tab[i+1][j];
			tab[i+1][j] = -1;
			tab[i][j] = 0;
		}
	}else if(desloca[1] == -1){
		if(j > 0){
			especie = tab[i][j-1];
			tab[i][j-1] = -1;
			tab[i][j] = 0;
		}
	}else if(desloca[1] == 1){
		if(j < 19){
			especie = tab[i][j+1];
			tab[i][j+1] = -1;
			tab[i][j] = 0;
		}
	}
	
	return especie;
}

/* Funcao: captura
 * Verifica se o jogador pode capturar o monstro de uma especie que esta na posicao do jogador.
 * Armazena o monstro capturado no vetor capturados e retorna 1 se conseguiu
 * capturar, ou 0 caso contrario.
 * Um monstro de especie 1 sempre eh capturado.
 *
 * Parametros:
 *   capturados: vetor de tamanho 151 (constante MONSTROS) com a quantidade de monstros de cada especie
 *               que o jogador possui. Desta forma, capturados[i] possui a quantidade de monstros
                 da especie (i+1) que o jogador possui.
 *   especie: numero da especie que pretende-se capturar.
 *
 * Retorno:
 *   1 se o monstro foi capturado, e 0 caso contrario.
 *   Note que o vetor capturados deve ser atualizado caso o monstro foi capturado.
 */
int captura(int capturados[MONSTROS], int especie) {

	int exp=0, i;

	for(i=0; i<MONSTROS; i++)
		exp = exp + (capturados[i] * (i+1));

	if(especie <= exp || especie == 1){
		capturados[especie-1] = capturados[especie-1] + 1;
		return 1;
	}else{
		return 0;
	}
}
