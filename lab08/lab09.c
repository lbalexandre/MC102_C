
/* Programa que determina se uma senha e adquada segudo algumas condicoes. A entrada consite em um dicionario de palavras 
reservadas e depois a senha a ser verificada. A saida consite em ok se a senha comprir todas as condicoes ou aponta 
as condicoes que a senha nao atende. */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){

	int numero = 0, tamanho = 0, tamanhoP = 0;
	char reservadas[200][21], senha[51]={0}, inverso[51]={0}, senha2[51]={0};
	int i=0, j=0, k=0, l=0, m=0, n=0, b=0; // Contadores
	

	//Entrada com a quantidade de palavras reservadas
	scanf("%d", &numero);

	//Entrada das palavras reservadas
	for(i=0; i<numero; i++){
		scanf("%s", reservadas[i]);
	}
	
	// Entrada da senha
	scanf("%s", senha);
	
	// Determinacao da quantidade de caracteres que a senha contem 
	tamanho = strlen(senha);
	
	if(tamanho < 8){
		printf("A senha deve conter pelo menos 8 caracteres\n");
		k++;
	}

	j=0;
	// Verificacao se a senha contem um letra maiuscula
	for(i=0; i<tamanho; i++){
		if(isupper(senha[i])){
			j = 1;	
		}
	}
		if(j==0){
			printf("A senha deve conter pelo menos uma letra maiuscula\n");
			k++;
		}

	j=0;
	// Verificacao se a senha contem um letra minuscula
	for(i=0; i<tamanho; i++){
		if(islower(senha[i])){
			j = 1;	
		}
	}
		if(j==0){
			printf("A senha deve conter pelo menos uma letra minuscula\n");
			k++;
		}

	j=0;
	// Verificacao se a senha contem ao menos um numero
	for(i=0; i<tamanho; i++){
		if(isdigit(senha[i])){
			j = 1;	
		}
	}
		if(j==0){
			printf("A senha deve conter pelo menos um numero\n");
			k++;
		}
	
	j=0;
	// Verificacao se a senha contem um simbolo
	for(i=0; i<tamanho; i++){
		if(isalnum(senha[i]) == 0){
			j = 1;	
		}
	}
		if(j==0){
			printf("A senha deve conter pelo menos um simbolo\n");
			k++;
		}

	// Verificacao se a senha é um palindromo
	inverso[tamanho] = '\0';
	j=tamanho - 1;
	i=0;
	while(i < tamanho){
		inverso[j] = senha[i];
		i++;
		j--;
	}

	if(strcmp(senha,inverso) == 0){
		printf("A senha e um palindromo\n");
		k++;
	}

	// Conversao dos carectes da senha que estap em maiusculo para minusculo
	for(i=0; i<tamanho; i++)
		senha2[i] = tolower(senha[i]);
	

	// Verificacao se a senha utiliza palavra reservada
	for(i=0; i<numero; i++){
		
		tamanhoP = strlen(reservadas[i]);
		
		if(tamanho == tamanhoP){
			if(strcmp(senha2,reservadas[i]) == 0){
				printf("A senha nao pode conter palavras reservadas\n");
				k++;
			}
		 }else if(tamanho > tamanhoP){
			for(j=0; j<tamanho; j++){
				if(senha2[j] == reservadas[i][0]){
					b=j;
					while(senha2[b] == reservadas[i][m]){
						l++;
						b++;
						m++;
					}
					m=0;
					if(l == tamanhoP){
						n++;
						k++;
						break;
						
					}

				}
				
			}
		l=0;
		}
	}

	if(n!=0)
		printf("A senha nao pode conter palavras reservadas\n");


	// Caso nao haja problemas, a senha é aceita
	if(k == 0){
		printf("ok\n");
	}

	return 0;
}
