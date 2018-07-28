//Programa que determina dado o pib de n anos, o trienio de maior crescimento percentual medio

#include <stdio.h>

int main(){
    
	int anos, anoi = 0, anof = 2, i, anoit = -2, anoft = 0;
    	float pib, pib_anterior = 0;
	float crescimento = 0, cres1 = 0, cres2 = 0, total = 0, media = 0;

	//Quantidade de anos a serem analisados
    	scanf("%d", &anos);
    
   	for(i=1; i<=anos; i++){
		scanf("%f", &pib);

		if(pib_anterior == 0){
			crescimento = 0;
		}else{
			crescimento = ((pib*100) / pib_anterior) - 100;
		}
		
		//Deteerminacao da media de um trienio
		media = (crescimento + cres1 + cres2) / 3;     

		if(media > total){
			total = media;
	
			if(cres2!=0){	
				anoi = anoit;
				anof = anoft;
			}
											
		}else if(total == 0){
			total = media;
		}
  		
		anoit++;
		anoft++;
		
		cres2 = cres1;
		cres1 = crescimento;
		pib_anterior = pib;
	}
	
	printf("a maior media de crescimento foi entre os anos %d e %d: %.1f\n", anoi, anof, total);

	return 0;
}
