

#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int *numeros; // Vetor com elementos, pode ser ordenado ou nao.
  int elementos; // Quantidade de elementos distintos
  int capacidade; // Tamanho do vetor 'numeros' para gerenciar alocacao de memoria
} conjunto;

/* Funcao: novo
 *
 * Cria um novo conjunto vazio (sem elementos) com um vetor numeros de determinada capacidade.
 * O conjunto deve ser alocado dinamicamente assim como o vetor elementos do mesmo.
 *
 * Parametros:
 *   capacidade: tamanho do vetor numeros que deve ser alocado
 *
 * Retorno:
 *   O endereço do novo conjunto alocado.
 *   A funcao deve ainda setar os campos elementos e capacidade corretamente.
 */
conjunto *novo(int capacidade){

	conjunto *conjNovo;

	conjNovo = malloc(sizeof(conjunto));

	conjNovo->numeros = malloc(capacidade*sizeof(int));
	conjNovo->capacidade = capacidade;
	conjNovo->elementos = 0;

	return conjNovo;
}

/* Funcao: aumenta_capacidade
 *
 * Aumenta a capacidade de um determinado conjunto.
 * Deve-se criar um novo vetor numeros com a capacidade especificada e trocar com o anterior,
 * onde, neste caso, lembre-se de liberar o vetor antigo que nao esta mais em uso.
 * O ponteiro do conjunto nao deve ser modificado, apenas seus dados internos.
 *
 * Parametros:
 *   conj: ponteiro do conjunto que tera a capacidade aumentada
 *   capacidade: nova capacidade
 *   A funcao deve setar os campos elementos e capacidade corretamente.
 */
void aumenta_capacidade(conjunto *conj, int capacidade){

	int i;
	conjunto *conjAux;

	conjAux = novo(capacidade);
	conjAux->elementos = conj->elementos;

	for(i=0; i<conj->elementos-1; i++)
		conjAux->numeros[i] = conj->numeros[i];

	free(conj->numeros);
	free(conj);
		
	conj = novo(capacidade);
	conj->elementos = conjAux->elementos;

	for(i=0; i<conjAux->elementos-1; i++)
		conj->numeros[i] = conjAux->numeros[i];

	free(conjAux->numeros);
	free(conjAux);
}

/* Funcao: deleta
 *
 * Libera a memoria alocada para o vetor elementos de um determinado conjunto.
 * A função deve também liberar a memória alocada para o conjunto.
 *
 * Parametros:
 *   conj: ponteiro do conjunto a ser deletado
 */
void deleta(conjunto *conj){

	free(conj->numeros);  
	free(conj);
}

/* Funcao: pertence
 *
 * Verifica se o conjunto apontado por conj possui o elemento num.
 * O conjunto nao deve ser modificado.
 *
 * Parametros:
 *   conj: ponteiro do conjunto de entrada
 *   num: elemento a ser verificado
 *
 * Retorno:
 *   1 se num pertence a conj, e 0 caso contrario
 */
int pertence(conjunto *conj, int num){

	int i;

	for(i=0; i<conj->elementos; i++){
		if(conj->numeros[i] == num)
			return 1;
	}
  	
	return 0;
}

/* Funcoes: contido
 *
 * Verifica se o conjunto apontado por conj1 esta contido no conjunto apontado por conj2.
 * Os conjuntos nao devem ser modificados.
 *
 * Parametros:
 *   conj1: ponteiro do conjunto de entrada que sera o primeiro operando
 *   conj2: ponteiro do conjunto de entrada que sera o segundo operando
 *
 * Retorno:
 *   0 se o conjunto 1 nao esta contido no conjunto 2,
 *   qualquer valor diferente caso contrario.
 */
int contido(conjunto *conj1, conjunto *conj2){

	int i, j, k=0;

	if(conj1->elementos > conj2->elementos){
		return 0;
	}else{
		for(i=0; i<conj1->elementos; i++){
			for(j=0; j<conj2->elementos; j++){
				if(conj1->numeros[i] == conj2->numeros[j])
					k++;
			}
		}

		if(k == conj1->elementos)
			return 1;
		else
			return 0;		
	}
}

/* Funcoes: adicao
 *
 * Inclui um elemento no conjunto sem permitir duas ou mais copias do mesmo elemento.
 * A quantidade de elementos no conjunto deve ser atualizada se o elemento for inserido.
 * Pode ser necessario aumentar a capacidade do conjunto.
 *
 * Parametros:
 *   conj: ponteiro do conjunto de entrada
 *   num: elemento a ser incluido
 */
void adicao(conjunto *conj, int num){
  
	int i, j=0;

	for(i=0; i<conj->elementos; i++){
		if(conj->numeros[i] == num)
			j++;
	}

	if(j == 0){	
		conj->elementos++;
		
		if(conj->elementos > conj->capacidade)
			aumenta_capacidade(conj, conj->capacidade+1);

		conj->numeros[conj->elementos-1] = num;						
	}
}

/* Funcoes: subtracao
 *
 * Remove um elemento de um conjunto apontado por conj.
 * A quantidade de elementos no conjunto deve ser atualizada se o elemento for removido.
 *
 * Parametros::
 *   conj: ponteiro do conjunto de entrada
 *   num: elemento a ser removido
 */
void subtracao(conjunto *conj, int num){

	int i;

	for(i=0; i<conj->elementos; i++){
		if(conj->numeros[i] == num){
			conj->numeros[i] = conj->numeros[conj->elementos-1];
			conj->elementos--;
		}	
	}
}

/* Funcoes: uniao, intersecao, diferenca
 *
 * Realiza a operacao do nome da funcao entre o conjunto conj1 e o conj2, respectivamente.
 * O resultado deve ser armazenado num novo conjunto alocado para esta finalidade.
 * Os conjuntos conj1 e conj2 nao devem ser modificados.
 *
 * Parametros:
 *   conj1: ponteiro do conjunto de entrada que sera o primeiro operando
 *   conj2: ponteiro do conjunto de entrada que sera o segundo operando
 *
 * Retorno:
 *   Ponteiro para um novo conjunto que contem o resultado da operacao
 */
conjunto *uniao(conjunto *conj1, conjunto *conj2){

	int i, j, k=0;
	conjunto *conjRes;

	conjRes = novo(conj1->elementos+conj2->elementos);

	conjRes->elementos = conj1->elementos;

	for(i=0; i<conj1->elementos; i++)
		conjRes->numeros[i] = conj1->numeros[i];
	
	for(i=0; i<conj2->elementos; i++){
		for(j=0; j<conjRes->elementos; j++){
			if(conj2->numeros[i] == conjRes->numeros[j])
				k++;
		}
		if(k == 0){
			conjRes->elementos++;
			conjRes->numeros[conjRes->elementos-1] = conj2->numeros[i];
		}
		k=0;
	}
			
	return conjRes;
}

conjunto *intersecao(conjunto *conj1, conjunto *conj2){

	int i, j;
	conjunto *conjRes;

	conjRes = novo(conj1->elementos+conj2->elementos);

	for(i=0; i<conj1->elementos; i++){
		for(j=0; j<conj2->elementos; j++){
			if(conj1->numeros[i] == conj2->numeros[j]){
				conjRes->elementos++;
				conjRes->numeros[conjRes->elementos-1] = conj1->numeros[i];
			}
		}
	}

	return conjRes;
}

conjunto *diferenca(conjunto *conj1, conjunto *conj2){

	int i, j, k=0;
	conjunto *conjRes;

	conjRes = novo(conj1->elementos);	

	for(i=0; i<conj1->elementos; i++){
		for(j=0; j<conj2->elementos; j++){
			if(conj1->numeros[i] == conj2->numeros[j])
				k++;
		}

		if(k == 0){
			conjRes->elementos++;
			conjRes->numeros[conjRes->elementos-1] = conj1->numeros[i];
		}
		k=0;
	}
					
	return conjRes;
}
