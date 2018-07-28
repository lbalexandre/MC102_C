/* Laboratorio 15 - Banco de Dados Geografico
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
	float x;
	float y;
} Ponto;

typedef struct{
	Ponto coordenadas;
	int inicioCEP;
	int fimCEP;
	int numHabitantes;
} Cidade;

/*
 * Funcao: distancia
 *
 * Parametros:
 *   a, b: pontos
 *
 * Retorno:
 *   A distancia euclidiana entre a e b.
 */
float distancia(Ponto a, Ponto b){

	return trunc(100 * sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y))) / 100.0; 
}

/* Funcao: consulta_cidade_por_cep
 *
 * Parametros:
 *   cidades: vetor de cidades (base de dados) 
 *       cep: CEP desejado
 *         n: tamanho do vetor de cidades 
 * 
 * Retorno:
 *   O indice da cidade que contem o CEP desejado, ou -1 se nao houver. 
 */
int consulta_cidade_por_cep(Cidade* cidades, int cep, int n){

	int i;

	for(i=0; i<n; i++){
		if(cep >= cidades[i].inicioCEP && cep <= cidades[i].fimCEP)
			return i;
	}

	return -1;	
}

/* Funcao: consulta_cidades_por_raio
 *
 * Parametros:
 *            cidades: vetor de cidades (base de dados) 
 *   cidadeReferencia: indice da cidade referencia (centro da circunferencia)
 *               raio: raio da busca
 *                  n: tamanho do vetor de cidades
 *           nRetorno: deve ser modificado para conter o tamanho do vetor de retorno
 *
 * Retorno:
 *   A sua funcao deve alocar dinamicamente um vetor resposta contendo os indices das cidades
 *   dentro do raio especificado (incluindo a cidade referencia). A função deve devolver 
 *   este vetor *ordenado pelas respectivas distancias da cidade referencia*.
 *   A funcao deve ainda setar o valor nRetorno com o tamanho do vetor.
 */
int* consulta_cidades_por_raio(Cidade* cidades, int cidadeReferencia, float raio, int n, int* nRetorno){
    
	int *indice;
	int i, j, tam=0, in;
	float D, Daux[n], aux;

	indice = malloc(n * sizeof(int));

	// Determinaçao das cidades que estao dentro do raio especificado	
	for(i=0; i<n; i++){
		D = distancia(cidades[cidadeReferencia].coordenadas, cidades[i].coordenadas);
			if(D < raio){
				indice[tam] = i;
				Daux[tam] = D;
				tam++;
			}
	}

	// Ordenação do vetor indice a partir do vetor Daux pelo metodo Bubble Sort
	for(i=tam-1; i>0; i--){
		for(j = 0; j < i; j++){
			if(Daux[j] > Daux[j+1]){
        			aux = Daux[j];
        			Daux[j] = Daux[j+1];
       				Daux[j+1] = aux;

				in = indice[j];
        			indice[j] = indice[j+1];
       				indice[j+1] = in;
     			}
    		}
 	 }

	*nRetorno = tam;

	return indice;	
}

/* Funcao: populacao_total
 *
 * Parametros:
 *            cidades: vetor de cidades (base de dados) 
 *   cidadeReferencia: indice da cidade referencia (centro da circunferencia)
 *               raio: raio da busca
 *                  n: tamanho do vetor de cidades
 *          
 * Retorno:
 *   O numero de habitantes das cidades que estao contidas no raio de busca
 */
int populacao_total(Cidade* cidades, int cidadeReferencia, float raio, int n){

	int i, populacao=0;
	float D;

	// Determinaçao das cidades que estao dentro do raio especificado
	// Soma de suas populacoes
	for(i=0; i<n; i++){
		D = distancia(cidades[cidadeReferencia].coordenadas, cidades[i].coordenadas);
			if(D < raio)
				populacao = populacao + cidades[i].numHabitantes;			
	}
	
	return populacao;
}

/* Funcao: mediana_da_populacao
 *
 * Parametros:
 *            cidades: vetor de cidades (base de dados) 
 *   cidadeReferencia: indice da cidade referencia (centro da circunferencia)
 *               raio: raio da busca
 *                  n: tamanho do vetor de cidades *          
 * Retorno:
 *   Mediana do numero de habitantes das cidades que estao contidas no raio de busca
 */
float mediana_da_populacao(Cidade* cidades, int cidadeReferencia, float raio, int n){

	int i, j, tam=0, pop[n], aux;
	float mediana, D;
	
	// Determinaçao das cidades que estao dentro do raio especificado	
	for(i=0; i<n; i++){
		D = distancia(cidades[cidadeReferencia].coordenadas, cidades[i].coordenadas);
			if(D < raio){
				pop[tam] = cidades[i].numHabitantes;
				tam++;
			}
	}

	// Ordenação do vetor pop pelo metodo Bubble Sort
	for(i=tam-1; i>0; i--){
		for(j = 0; j < i; j++){
			if(pop[j] > pop[j+1]){
        			aux = pop[j];
        			pop[j] = pop[j+1];
       				pop[j+1] = aux;
     			}
    		}
 	 }

	//for(i=0; i<tam; i++)
		//printf("%d ", pop[i]);

	// Determinao da mediana das populacoes
	i = tam / 2;
	if(tam % 2 == 0)
		mediana = ((float)pop[i] + pop[i-1]) / 2;
	else
		mediana = pop[i];
	
	return mediana;
}
