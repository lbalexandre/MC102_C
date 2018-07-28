//Programa que determina o vencedor da luta entra Ryu e Ken, personagens de Street Fighter

#include <stdio.h>

int main(){

    int ryu = 0, ken = 0, golpe;
    int Rr = 0, Rk = 0 ;

    // Entrada com os valores dos golpes
    scanf("%d", &golpe);

    do{
        do{
            ryu = ryu + golpe;
            scanf("%d", &golpe);
        }while(golpe > 0);

        do{
            ken = ken + (golpe*(-1));
            scanf("%d", &golpe);
        }while(golpe < 0);

        //Atribuicao do vencedor do round
        if(ryu > ken){
            Rr++;
        }else{
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
