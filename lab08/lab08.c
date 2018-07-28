/* 	Programa que com a estrada de uma certa base de dados de ataques antes e depois da evolucao de Pokemon
 estima qual sera os ataque de outros Pokemon depois da evolucao.
	A entrada é composta por tres partes, primeiro a quantidade de Pokemon que o banco de dados terá, depois
depois o banco de dados propriamente dito e por ultimo os Pokemon que serao verificados.
	A saida é composta pelas estimativas de poder que o Pokemon terao apos a evolução. */

#include <stdio.h>

int main(){
	
	int base, pokemon, especie[300], especie2[300], especie3[300], teste[300];
	float PCa[151], PCf[300], PCaa[151], PCff[300], PCa1[300], PCf1[300];
	float quantidade, soma;
	float multiplicador[300], media_mult[300];
	int i, j, k, l, m, n; // Contadores

	// Quantidade de pokemon na base de dados
	scanf("%d", &base);
		
	// Atribuicao da especie, e de seus poder antes de depois da evolucao
	for(i=0; i<base; i++){
		scanf("%d %f %f", &especie[i], &PCa[i], &PCf[i]);
	}

	// Entradas dos Pokemon que terao seus PCf estimados
	i=0;
	k=-1;
	do{
		scanf("%d %f", &especie2[i], &PCaa[i]);		
		k++;
		i++;	
	}while(especie2[k] != 0 && PCaa[k] != 0);

	// Retirando as especies reptidas
	n=0;
	for(i=0; i<k; i++) {
		if(i == 0) {
			teste[i] = especie2[i];
			n++;
		}else{
			m=0;
			for(j=0; j<n; j++) {
				if(especie2[i] == teste[j]) {
					m++;
			}
      		}
			if(m<1){
				teste[n] = especie2[i];
 				n++;
			}
		}
	}
	
	// A partir dos Pokemon que serao verificados, determincao de quais Pokemon da base de dados serao utilizados nos calculos
	m=0; l=0; n=0;
	for(i=0; i<k; i++){
		for(j=0; j<base; j++){
			if(teste[i] == especie[j]){
				if(m != 0){
					l++;
				}
				especie3[l] = especie[j];
				PCa1[l] = PCa[j];
				PCf1[l] = PCf[j];
				m++;
				n++;			
			}
		}
		m=0;
		l++;
	}
	
	// Determinacao do numero da menor especie dos Pokemon da base de dados
	pokemon = especie3[0];
	for(i=0; i<n; i++){
		if(especie3[i] < pokemon){
			pokemon = especie3[i];
		}
	}
	
	m=0;
	// Calculo do multiplicador medio de cada especie
	for(j=0; j<300; j++){		
		for(i=0; i<n; i++){
			if(pokemon == especie3[i]){
				multiplicador[i] = PCf1[i] / PCa1[i];
				soma = soma + multiplicador[i];
				quantidade++;
			}			
		}
		if(soma != 0){
			media_mult[m] = soma / quantidade;
			m++;
		}

		quantidade = 0;
		soma = 0;
		pokemon++;
	}

	// Determinacao da menor especie dos Pokemon que serao verificados
	pokemon = especie2[0];
	for(i=0; i<k; i++){
		if(especie2[i] < pokemon){
			pokemon = especie2[i];
		}
	}

	// Multiplicacao do PCa pela media do multiplicador respectivo de cada especie
	j=0; m=1;
	for(l=0; l<300; l++){
		for(i=0; i<k; i++){	
			if(pokemon == especie2[i]){
				if(m == 0){
					j++;
				}
				PCff[i] = PCaa[i] * media_mult[j] + 0.5;	
				m++;	
			}	
		}
		m = 0;
		pokemon++;
	}

	// Valor dos PCf estimados
	for(i=0; i<k; i++){
		printf("%.0f\n", PCff[i]);				
	}	

	return 0;
}
