

#include <stdio.h>

/* Funcao: pertence
 *
 * Parametros:
 *   conj: vetor contendo o conjunto de entrada
 *    tam: tamanho do conjunto
 *    num: elemento a ser verificado pertinencia
 *
 * Retorno:
 *   1 se num pertence a conj e 0 caso contrario
 */
int pertence(int conj[], int tam, int num){

	int i;

	for(i=0; i<tam; i++){
		if(conj[i] == num)
			return 1;	
	}
	
	return 0;
}

/* Funcao: contido
 *
 * Parametros:
 *   conj1: vetor contendo um conjunto de entrada
 *   conj2: vetor contendo um conjunto de entrada
 *    tam1: tamanho do conjunto conj1
 *    tam2: tamanho do conjunto conj2
 *
 * Retorno:
 *   1 se conj1 esta contido em conj2 e 0 caso contrario
 */
int contido(int conj1[], int conj2[], int tam1, int tam2){

	int i, j, k = 0;

	if(tam1 > tam2){
		return 0;
	}else{
		for(i=0; i<tam1; i++){
			for(j=0; j<tam2; j++){
				if(conj1[i] == conj2[j])
					k++;
			}
		}

		if(k == tam1)
			return 1;
		else
			return 0;
			
	}
}

/* Funcoes: adicao e subtracao
 *
 * Parametros:
 *   conj: vetor contendo o conjunto que tera incluso ou removido o elemento
 *    tam: tamanho do conjunto
 *    num: elemento a ser adicionado ou removido
 *
 * Retorno:
 *   tamanho do conjunto apos a operacao.
 */
int adicao(int conj[], int tam, int num){

	int i, j=0;
	
	for(i=0; i<tam; i++){
		if(conj[i] == num)
			j++;
	}
		
	if(j == 0){
		conj[tam] = num;
		tam++;
	}
			
	return tam;	
}

int subtracao(int conj[], int tam, int num){

	int i, j;

	for(i=0; i<tam; i++){
		if(conj[i] == num){
			for(j=i; j<tam; j++)
				conj[j] = conj[j+1];
		}
	}
	tam--;

	return tam;	
}

/* Funcoes: uniao, intersecao e diferenca
 *
 * Parametros:
 *   conjRes: vetor contendo o conjunto de saida/resultado da operacao
 *     conj1: vetor contendo o conjunto de entrada do primeiro operando
 *     conj2: vetor contendo o conjunto de entrada do segundo operando
 *      tam1: tamanho do conjunto conj1
 *      tam2: tamanho do conjunto conj2
 *
 * Retorno:
 *   tamanho do conjunto de saida conjRes.
 */
int uniao(int conjRes[], int conj1[], int conj2[], int tam1, int tam2){

	int i, j, k=0, n=1;

	conjRes[0] = conj1[0];

	for(i=1; i<tam1; i++){
		for(j=0; j<tam1; j++){
			if(conj1[i] == conjRes[j])
				k++;
		}
		if(k == 0){
			conjRes[n] = conj1[1];
			n++;
		}
		k=0;
	}

	for(i=0; i<tam2; i++){
		for(j=0; j<tam2; j++){
			if(conj2[i] == conjRes[j])
				k++;

		}
	}
	
	return n;
}

int intersecao(int conjRes[], int conj1[], int conj2[], int tam1, int tam2){

	int i, j, k=0;

	for(i=0; i<tam1; i++){
		for(j=0; j<tam2; j++){
			if(conj1[i] == conj2[j]){
				conjRes[k] = conj1[i];
				k++;
			}
		}
	}

	return k;
}

int diferenca(int conjRes[], int conj1[], int conj2[], int tam1, int tam2){

	int i, j, k=0, tamR = 0;

	for(i=0; i<tam1; i++){
		for(j=0; j<tam2; j++){
			if(conj1[i] != conj2[j]){
				k++;
			}
		}
		if(k == tam1){
			conjRes[i] = conj1[i];
			tamR++; 
		}
		k=0;
	}

	return tamR;
}
