//Programa que determina o vencedor da luta entra Ryu e Ken, personagens de Street Fighter

#include <stdio.h>

	int main(){

	int ryu = 0, ken = 0, Rr = 0, Rk = 0;
	int golpe = 0, perfeito = 0, especial =0, posicao = 0; 
	int i = 0, j = 0;

	// Entrada com os valores dos golpes
	do{
		do{
			// Verificacao se o numero do golpe de Ryu é perfeito, caso seja, é multiplicado por 3
			// Caso não seja perfeito, verificacao se o numero do golpe de Ryu é triangular, caso seja, é multiplicado por 2

			ryu = ryu + golpe;
			scanf("%d", &golpe);

			if(golpe > 0){			
		
				for(i=1; i<=golpe/2; i++){
					perfeito = golpe % i;
						if(perfeito == 0){
							especial = especial + i;
						}	
				}
				if(especial == golpe){
					golpe = 3 * golpe;	
				}else{	
					j=0;
					do{	
						j++;
						posicao = j*(j+1) / 2;
					}while(posicao != golpe && j != 55);
				
					if(golpe == posicao){
						golpe = 2 * golpe;			
					}
				}
			}else{
				golpe = golpe*(-1);
			
				for(i=1; i<=golpe/2; i++){
					perfeito = golpe % i;
						if(perfeito == 0){
							especial = especial + i;
						}	
				}
				if(especial == golpe){
					golpe = 3 * golpe;	
				}else{	
					j=0;
					do{	
						j++;
						posicao = j*(j+1) / 2;
					}while(posicao != golpe && j != 55);
				
					if(golpe == posicao){
						golpe = 2 * golpe;			
					}
				}
			golpe = golpe*(-1);
			}

			especial = 0;

		}while(golpe > 0);

		do{	
			// Verificacao se o numero do golpe de Ken é perfeito, caso seja, é multiplicado por 3
			// Caso não seja perfeito, verificacao se o numero do golpe de Ken é triangular, caso seja, é multiplicado por 2

			ken = ken + golpe*(-1);
				scanf("%d", &golpe);
	
				if(golpe < 0){
					golpe = golpe*(-1);

					for(i=1; i<=golpe/2; i++){
						perfeito = golpe % i;
							if(perfeito == 0){
								especial = especial + i;
							}	
					}
					if(especial == golpe){
							golpe = 3 * golpe;	
					}else{	
						j=0;
						do{	
							j++;
							posicao = j*(j+1) / 2;
						}while(posicao != golpe && j != 55);
				
						if(golpe == posicao){
							golpe = 2 * golpe;			
						}
					}
				golpe = golpe*(-1);
				}else{
					for(i=1; i<=golpe/2; i++){
						perfeito = golpe % i;
							if(perfeito == 0){
								especial = especial + i;
							}	
					}
					if(especial == golpe){
						golpe = 3 * golpe;	
					}else{	
						j=0;
						do{	
							j++;
							posicao = j*(j+1) / 2;
						}while(posicao != golpe && j != 55);
				
						if(golpe == posicao){
							golpe = 2 * golpe;			
						}
					}
				}
			especial = 0;
			
		}while(golpe < 0);
	
        	//Atribuicao do vencedor do round
		if(ryu > ken){
 			Rr++;
		}else if(ryu < ken){
			Rk++;
		}

		ryu = 0; 
		ken = 0;  
	
	}while(golpe != 0);

	//Determinacao de quem venceu mais rounds ou se houve empate
	if(Rr > Rk){
        	printf("Ryu venceu\n");
	}else if(Rk > Rr){
       		 printf("Ken venceu\n");
	}else{
       		 printf("empatou\n");
   	}

    return 0;
}
