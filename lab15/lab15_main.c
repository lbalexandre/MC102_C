#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float x;
    float y;
} Ponto;

typedef struct {
    Ponto coordenadas;
    int inicioCEP;
    int fimCEP;
    int numHabitantes;
} Cidade;

int consulta_cidade_por_cep(Cidade* cidades, int cep, int n);
int* consulta_cidades_por_raio(Cidade* cidades, int cidadeReferencia, float raio, int n, int* nRetorno);
int populacao_total(Cidade* cidades, int cidadeReferencia, float raio, int n);
float mediana_da_populacao(Cidade* cidades, int cidadeReferencia, float raio, int n);

int main() {
    int i, j;
    int n, q;

    Ponto coordenadas;
    int inicioCEP;
    int fimCEP;
    int numHabitantes;

    int tipoConsulta;
    int cidadeReferencia;
    int cep;
    float raio;

    int* cidadesRetorno;
    int nRetorno;

    scanf("%d", &n);

    Cidade* cidades = (Cidade*)malloc(n * sizeof(Cidade));

    for (i = 0; i < n; i++) {
        scanf("%f %f %d %d %d", &coordenadas.x, &coordenadas.y, &inicioCEP, &fimCEP, &numHabitantes);
        
        cidades[i].coordenadas = coordenadas;
        cidades[i].inicioCEP = inicioCEP;
        cidades[i].fimCEP = fimCEP;
        cidades[i].numHabitantes = numHabitantes;
    }

    scanf("%d", &q);

    for (i = 0; i < q; i++) {
        printf("Consulta %d:\n", i);
        
        scanf("%d", &tipoConsulta);

        switch(tipoConsulta) {
        case 0:
            scanf("%d", &cep);
            int res = consulta_cidade_por_cep(cidades, cep, n);
            if (res < 0) {
                printf("Nao ha uma cidade com o CEP %d\n", cep);
            } else {
                printf("Cidade com CEP %d: %d\n", cep, consulta_cidade_por_cep(cidades, cep, n));
            }
            break;
        case 1:
            scanf("%d %f", &cidadeReferencia, &raio);
            cidadesRetorno = consulta_cidades_por_raio(cidades, cidadeReferencia, raio, n, &nRetorno);

            printf("Cidades no raio de %.0f:\n", raio);
            for (j = 0; j < nRetorno; j++) {
                printf("%d\n", cidadesRetorno[j]);
            }
            
            break;
        case 2:
            scanf("%d %f", &cidadeReferencia, &raio);
            printf("Populacao total: %d\n", populacao_total(cidades, cidadeReferencia, raio, n));
            break;
        case 3:
            scanf("%d %f", &cidadeReferencia, &raio);
            printf("Mediana da populacao: %.1f\n", mediana_da_populacao(cidades, cidadeReferencia, raio, n));
            break;
        }
    }

    free(cidades);

    return 0;
}
