// Programa que calcula a media da disciplina mc102

#include <stdio.h> 

int main(){
    
    float p1, p2, media_labs;
    float media, media_provas, exame, final;

    scanf("%f %f %f", &p1, &p2, &media_labs);

    // Calculo da media das provas

    media_provas = (2*p1 + 3*p2) / 5;

    // Calculo da media

    media = (3*media_provas*media_labs) / (media_provas + 2*media_labs);
        
    // Teste que verifica se o aluno precisara do exame
    
    if(media < 5 && media >= 2.5){
        scanf("%f", &exame);
		if(exame > 5){
			final = 5;
		}else{
        		final = (media + exame) / 2;
		}     	
    }else{
        final = media;
    }

    printf("%.1f\n", media_provas);
    printf("%.1f\n", media);
    printf("%.1f\n", final);

    return 0;
}
