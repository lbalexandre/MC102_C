

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int **alocarMatriz(int linhas, int colunas);
void desalocarMatriz(int **matriz, int linhas, int colunas);
int **fatorRGB(int **imagem, int **imagemRGB, int h, int l, int k);
int **Escala_de_Cinza(int **novaRGB, int **imagemR, int **imagemG, int **imagemB, int h, int l);
int **NovaIm(int **novaImagem, int **novaRGB, int h, int l, int k);
int maxRGB(int **fatorRGB, int h, int l);
int minRGB(int **fatorRGB, int h, int l);
int **Esticar_Contraste(int **novaRGB, int **imagemRGB, int RGBmax, int RGBmin, int h, int l);

int main(int argc, char **argv){

 	if(argc != 3){
		fprintf(stderr, "Argumentos invalidos. Use:\n");
		fprintf(stderr, "./lab16 <arqEntrada> <arqSaida>\n");
		fprintf(stderr, "Usado:");

		for (int i=0; i<argc; i++)
			fprintf(stderr, " %s", argv[i]);
  
		fprintf(stderr, "\n");

		return 1;
	}

	char efeito[20];
	char *arqEntrada = argv[1];
	char *arqSaida = argv[2];
	char tipo[10];
	int l, h, max;
	int **imagem, **novaImagem;
	int **imagemR, **imagemG, **imagemB;
	int **novaR, **novaG, **novaB;
	int Rmax, Rmin, Gmax, Gmin, Bmax, Bmin;	
	int i, j, k;
	
	// Efeito a ser aplicado na imagem
	scanf("%s", efeito);

	// Abertura do arquivo da imagem de entrada
	FILE *imEntrada;
	imEntrada = fopen(arqEntrada, "r");

	// Le dados do cabecalho
	fscanf(imEntrada, "%s", tipo);
	fscanf(imEntrada, "%d %d %d", &l, &h, &max);

	// Alocacao de memoria para a matriz imagem
	imagem = alocarMatriz(h, 3*l);
	
	// Le os dados da imagem e armazena na matriz imagem
	for(i=0; i<h; i++){
		for(j=0; j<3*l; j++)
			fscanf(imEntrada, "%d", &imagem[i][j]);	
	}

	// Separa cada pixel da imagem em fatores RGB, e os armazenas em matrizes individuais

	// Fator R
	imagemR = alocarMatriz(h, l);

	k = 0;
	imagemR = fatorRGB(imagem, imagemR, h, l, k);

	// Fator G
	imagemG = alocarMatriz(h, l);

	k = 1;
	imagemG = fatorRGB(imagem, imagemG, h, l, k);

	// Fator B
	imagemB = alocarMatriz(h, l);
	
	k = 2;
	imagemB = fatorRGB(imagem, imagemB, h, l, k);

	// Alocacao de memoria para os novo fatores RGB
	novaR = alocarMatriz(h, l);
	novaB = alocarMatriz(h, l);
	novaG = alocarMatriz(h, l);

	// Fechamento do arquivo de entrada que nao sera mais utilizado
	fclose(imEntrada);

	// Aplicao do efeito escolhido
	if(efeito[0] == 'c'){
		// Efeito Escala de Cinza

		// Atribuicao dos novos valores de cada fator
		novaR = Escala_de_Cinza(novaR, imagemR, imagemG, imagemB, h, l);
		novaG = Escala_de_Cinza(novaG, imagemR, imagemG, imagemB, h, l);
		novaB = Escala_de_Cinza(novaB, imagemR, imagemG, imagemB, h, l);
		
	}else{
		// Efeito Esticar Contraste
	
		// Determinacao do valor maximo e minimo de cada fator RGB
		Rmax = maxRGB(imagemR, h, l);
		Rmin = minRGB(imagemR, h, l);
	
		Gmax = maxRGB(imagemG, h, l);
		Gmin = minRGB(imagemG, h, l);
		
		Bmax = maxRGB(imagemB, h, l);
		Bmin = minRGB(imagemB, h, l);

		novaR = Esticar_Contraste(novaR, imagemR, Rmax, Rmin, h, l);
		novaG = Esticar_Contraste(novaG, imagemG, Gmax, Gmin, h, l);
		novaB = Esticar_Contraste(novaB, imagemB, Bmax, Bmin, h, l);
	}

	// Alocacao de memoria para a matriz novaImagem
	novaImagem = alocarMatriz(h, 3*l);

	// A matriz novaImagem recebe cada fator novo RGB formando a nova imagem com o efeito aplicado

	k=0;
	novaImagem = NovaIm(novaImagem, novaR, h, l, k);

	k=1;
	novaImagem = NovaIm(novaImagem, novaG, h, l, k);

	k=2;
	novaImagem = NovaIm(novaImagem, novaB, h, l, k);	

	// Libercao da memoria que nao sera mais usada
	desalocarMatriz(imagem, h, 3*l);
	desalocarMatriz(novaR, h, l);
	desalocarMatriz(novaG, h, l);
	desalocarMatriz(novaB, h, l);
	
	// Abertura do arquivo da imagem de saida	
	FILE *imSaida;
	imSaida = fopen(arqSaida, "w");

	// Imprime dados do cabecalho
	fprintf(imSaida, "%s\n", tipo);
	fprintf(imSaida, "%d %d\n%d\n", l, h, max);
	
	// Imprime os valores da matriz novaImagem no arquivo de saida
	for(i=0; i<h; i++){
		for(j=0; j<3*l; j++)
			fprintf(imSaida, "%d ", novaImagem[i][j]);
		fprintf(imSaida, "\n");	
	}

	fclose(imSaida);
	
	return 0;
}

// Funcao que alocar a memoria necessaria para a matrizes utilizadas
int **alocarMatriz(int linhas, int colunas){
	
	int i;

	int **matriz = malloc(linhas * sizeof(int *));
	for(i=0; i<linhas; i++)
		matriz[i] = malloc(colunas * sizeof(int));

	return matriz;
}

// Funcao que desalocar a memoria nao mais necessaria
void desalocarMatriz(int **matriz, int linhas, int colunas){

	int i;

	for(i=0; i<linhas; i++)
		free(matriz[i]);

	free(matriz);
}

// Separa cada pixel da imagem em fatores RGB, e o armazenas em matrizes individuais
int **fatorRGB(int **imagem, int **imagemRGB, int h, int l, int k){

	int i, j, y;
	
	for(i=0; i<h; i++){
		y=k;
		for(j=0; j<l; j++, y=y+3)
			imagemRGB[i][j] = imagem[i][y];
	}
	
	return imagemRGB;
}

// Modifica os fatores RGB os deixando em escala de cinza 
int **Escala_de_Cinza(int **novaRGB, int **imagemR, int **imagemG, int **imagemB, int h, int l){

	int i, j;

	for(i=0; i<h; i++){
		for(j=0; j<l; j++)
			novaRGB[i][j] = floor(((float)imagemR[i][j] + (float)imagemG[i][j] + (float)imagemB[i][j]) / 3);
	}

	return novaRGB;
}

// Juncao dos fatores RBG para formacao da nova imagem com o efeito
int **NovaIm(int **novaImagem, int **novaRGB, int h, int l, int k){
		
	int i, j, y;

	for(i=0; i<h; i++){
		y=k;
		for(j=0; j<l; j++, y=y+3)
			novaImagem[i][y] = novaRGB[i][j];
	}

	return novaImagem;
}

// Funcao que encontra o valor maximo de um termo RGB
int maxRGB(int **fatorRGB, int h, int l){
	
	int i, j;
	int max = fatorRGB[0][0];

	for(i=0; i<h; i++){
		for(j=0; j<l; j++){
			if(fatorRGB[i][j] > max)
				max = fatorRGB[i][j];
		}
	}
	
	return max;
}

// Funcao que encontra o valor minimo de um termo RGB
int minRGB(int **fatorRGB, int h, int l){
	
	int i, j;
	int min = fatorRGB[0][0];

	for(i=0; i<h; i++){
		for(j=0; j<l; j++){
			if(fatorRGB[i][j] < min)
				min = fatorRGB[i][j];
		}
	}
	
	return min;
}

// Modifica os fatores RGB esticando o contraste
int **Esticar_Contraste(int **novaRGB, int **imagemRGB, int RGBmax, int RGBmin, int h, int l){ 

	int i, j;

	for(i=0; i<h; i++){
		for(j=0; j<l; j++)
			novaRGB[i][j] = floor(((float)imagemRGB[i][j] - (float)RGBmin) * 255)/((float)RGBmax - (float)RGBmin);
		}

	return novaRGB;
}	
