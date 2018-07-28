

#include <stdio.h>

#define MAX 50
 
void verificacao(int matriz[][MAX], int n, int op, int hierarquia[], int *k);
void ordena(int hierarquia[], int *tam);

int main(){

	int tam, empresa[MAX][MAX];
	int funcionario;
	int i, j, k=0;
	int hierarquia[MAX] = {0};
	
	// Leitura do tamanho da matriz
	scanf("%d", &tam);

	// Identificador do funcionario que tera sua hierarquia verificada
	scanf("%d", &funcionario);

	// Leitura das linhas da matriz que descrevem a hierarquia da empresa
	for(i=0; i<tam; i++){
		for(j=0; j<tam; j++)
			scanf("%d", &empresa[i][j]);
	}
	
	// Funcao que verifica a hierarquia
	verificacao(empresa, tam, funcionario, hierarquia, &k);

	// Ordena a hierarquia
	ordena(hierarquia, &k);

	// Impressao o numero indentificador do funcionario que tera sua hierarquia verificada
	if(k == 0)
		printf("%d", funcionario);
	else
		printf("%d ", funcionario);

	// Imprime os indentificadores de cada cargo 
	for(i=0; i<k; i++){
		if(i == k-1)
			printf("%d", hierarquia[k-1]);
		else
			printf("%d ", hierarquia[i]);
	}

	printf("\n");
	
	return 0;
}

// Funcao que verifica toda a hierarquia ligada a um dado cargo
void verificacao(int matriz[][MAX], int n, int op, int hierarquia[], int *k){

	int j;
	
	for(j=0; j<n; j++){
		if(matriz[op][j] == 1){	
			hierarquia[*k] = j;
			(*k)++;
			verificacao(matriz, n, j, hierarquia, k);
		}
	}
}

// Ordena os cargos do menor identificador para o maior
void ordena(int hierarquia[], int *tam){

	int i, j, aux;
	
	for(i=*tam-1; i>0; i--){
		for(j=0; j<i; j++){
			if(hierarquia[j] > hierarquia[j+1]){
        			aux = hierarquia[j];
        			hierarquia[j] = hierarquia[j+1];
       				hierarquia[j+1] = aux;
     			}
    		}
 	 }	
}
