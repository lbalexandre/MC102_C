#include <stdio.h>

#define ALTURA_TABULEIRO 10
#define LARGURA_TABULEIRO 10

void atualiza_posicao(int *l, int *a, int *x, int desl, int rot);
int encontra_y(int matriz[ALTURA_TABULEIRO][LARGURA_TABULEIRO], int l, int x);
int posicao_final_valida(int a,  int y);
void posiciona_bloco(int matriz[ALTURA_TABULEIRO][LARGURA_TABULEIRO], int l, int a, int x, int y);
int atualiza_matriz(int matriz[ALTURA_TABULEIRO][LARGURA_TABULEIRO]);

int main() {
    int n;
    int l, a, x, desl, rot, y, valido, pontos = 0;
    int i, j, k;

    int matriz[ALTURA_TABULEIRO][LARGURA_TABULEIRO];

    for (j = 0; j < ALTURA_TABULEIRO; j++) {
        for (i = 0; i < LARGURA_TABULEIRO; i++) {
            matriz[j][i] = 0;
        }
    }
    
    scanf("%d", &n);

    for (k = 0; k < n; k++) {
        scanf("%d %d %d %d %d", &l, &a, &x, &desl, &rot);

        atualiza_posicao(&l, &a, &x, desl, rot);
        y = encontra_y(matriz, l, x);
        valido = posicao_final_valida(a, y);

        if (valido) {
            posiciona_bloco(matriz, l, a, x, y);
            pontos += atualiza_matriz(matriz);

            printf("bloco %d\n", k);
            printf("%d pontos\n", pontos);
    
            for (j = ALTURA_TABULEIRO - 1; j >= 0; j--) {
                for (i = 0; i < LARGURA_TABULEIRO; i++) {
                    printf("%d", matriz[j][i]);
                }

                printf("\n");
            }
        } else {
            break;
        }
    }

    return 0;
}
