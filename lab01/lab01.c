// Programa para calcular a circuferencia da Terra

#include <stdio.h>

int main(){

	float distancia, angulo;
	float Ce, Ckm;

	scanf("%f", &distancia);
	scanf("%f", &angulo);	
	
	// Circinferencia em Estadios
	Ce = (distancia * 360) / angulo;
	
	// Conversao para quilometros
	Ckm = (Ce * 176.4) / 1000;

	printf("%.1f\n", Ce);
	printf("%.1f\n", Ckm);
	
	return 0;
}
