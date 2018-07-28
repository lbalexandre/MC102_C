// Pragrama que verifica se um triangulo composto por 6 numeros é magico

#include <stdio.h>

int main(){

	int v1, v2, v3, v4, v5, v6;
	int soma1, soma2, soma3;
	
	scanf("%d %d %d %d %d %d", &v1, &v2, &v3, &v4, &v5, &v6);

	soma1 = v1 + v2 + v3;
	soma2 = v3 + v4 + v5;
	soma3 = v5 + v6 + v1;

	if((soma1 == soma2) && (soma1 == soma3) && (soma2 == soma3)){	
		printf("sim\n");
	}else{
		printf("nao\n");
	}

	return  0;
}
