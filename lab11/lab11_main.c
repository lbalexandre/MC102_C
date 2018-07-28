#include <stdio.h>

int pertence(int conj[], int tam, int num);
int contido(int conj1[], int conj2[], int tam1, int tam2);
int adicao(int conj[], int tam, int num);
int subtracao(int conj[], int tam, int num);
int uniao(int destRes[], int conj1[], int conj2[], int tam1, int tam2);
int intersecao(int destRes[], int conj1[], int conj2[], int tam1, int tam2);
int diferenca(int destRes[], int conj1[], int conj2[], int tam1, int tam2);

#define CONJ_TAM 20

/* Funcao: bubble_sort
 *
 * Parametros:
 *    vet: vetor de inteiros a ser ordenado
 *    tam: tamanho/quantidade de elementos do vetor 'vet'
 *
 * Retorno:
 *   O vetor e ordenado "in place", no proprio vetor de entrada.
 *   Nao ha retorno da funcao.
 *
 * Descricao:
 *   Essa e uma simples funcao para ordenar os elementos do vetor de entrada
 *   'vet'. Ela usa o algoritmo "bubble sort".
 */
void bubble_sort(int vet[], int tam) {
  int i, j, aux;

  for (i = tam - 1; i > 0; i--) {
    for (j = 0; j < i; j++) {
      if (vet[j] > vet[j + 1]) {
        aux = vet[j];
        vet[j] = vet[j + 1];
        vet[j + 1] = aux;
      }
    }
  }
}

/* Funcao: copia_conjunto
 *
 * Parametros:
 *   conjRes: vetor contendo o conjunto de saida/resultado da operacao
 *      conj: vetor contendo o conjunto de entrada
 *       tam: tamanho do conjunto 'conj'
 *
 * Retorno:
 *   A copia e retornada no parametro 'conjRes'.
 *   Nao ha retorno da funcao.
 *
 * Descricao:
 *   Essa é uma simples funcao que copia o conteudo do conjunto 'conj' para
 *   conjunto 'conjRes'. No final conjRes tem tamanho 'tam'.
 */
void copia_conjunto(int conjRes[], int conj[], int tam) {
  int i = 0;
  for (i = 0; i < tam; i++) {
    conjRes[i] = conj[i];
  }
}

/* Funcao: imprime_conjunto
 *
 * Parametros:
 *   conj: vetor contendo o conjunto de entrada
 *    tam: tamanho do conjunto 'conj'
 *   nome: nome/descricao do conjunto a ser impresso
 *
 * Retorno:
 *   nao ha retorno.
 *
 * Descricao:
 *   Essa funcao imprime (na saida padrao) um conjunto no formato
 *   "<nome> = {x1, x2, ... , xn}", onde nome e o valor do parametro 'nome' e
 *   x1, x2, ..., xn sao os elementos do conjunto 'conj' de tamanho 'tam'. Note
 *   na impressao nao ha espacos entre as chaves e o primeiro e ultimo elemento.
 *   Tambem nao ha virgula apos o ultimo elemento. Caso o vetor esteja vazio,
 *   com 'tam == 0', o conjunto resultado e vazio, sem espaco entre os
 *   conjuntos, assim: "<nome> = {}".
 *   Essa funcao sempre imprime uma marca de final de linha '\n' ao final da
 *   impressao.
 *   A impressao sempre imprime os valores do conjunto em ordem crescente, porem
 *   nao altera os valores do conjunto original. Para isso, o conjunto a ser
 *   impresso e copiado para um vetor temporario 'conj_temp' e depois ordenados,
 *   antes de realizar a impressao.
 */
void imprime_conjunto(int *conj, int tam, char *nome) {
  int i = 0;
  int conj_temp[CONJ_TAM];
  copia_conjunto(conj_temp, conj, tam);
  conj = conj_temp;
  bubble_sort(conj, tam);
  printf("%s = {", nome);
  for (i = 0; i < tam - 1; i++) {
    printf("%d, ", conj[i]);
  }
  if (tam > 0) {
    printf("%d", conj[tam - 1]);
  }
  printf("}\n");
}

/* Funcao: analisa_atribuicao
 *
 * Parametros:
 *   conj: vetor contendo o conjunto de saida
 *    tam: tamanho final do conjunto 'conj'
 *
 * Retorno:
 *   'conj' contem o conjunto reinicializado e incluido todos os elementos
 *   atribuidos e 'tam' tambem e atualizado com o novo tamanho.
 *   Nao ha retorno da funcao.
 *
 * Descricao:
 *   Na atribuicao o conteudo de um dos conjuntos e substituido pelos valores
 *   entre chaves da leitura.
 *   Essa funcao apaga o conteudo do conjunto 'conj' reiniciando o seu tamanho.
 *   Em seguida le da entrada padrao o conteudo a ser atribuido ao conjunto, um
 *   valor por vez, adicionando os valores ao conjunto.
 */
void analisa_atribuicao(int *conj, int *tam) {

  int num = 0;
  *tam = 0;
  scanf(" { ");
  while (0 < scanf(" %d ,", &num)) {
    *tam = adicao(conj, *tam, num);
  }
}

/* Funcao: analisa_add_sub
 *
 * Parametros:
 *     op: qual operacao realizar, valores: adicao '+' ou subtracao '-'
 *   conj: vetor contendo o conjunto de entrada
 *    tam: tamanho do conjunto 'conj'
 *
 * Retorno:
 *   'conj' contem o conjunto atualizado com a adicao ou remocao de um elemento
 *   e 'tam' tambem e atualizado com o novo tamanho.
 *   Nao ha retorno da funcao.
 *
 * Descricao:
 *   Le da entrada padrao o numero a ser adicionado ou subtraido do conjunto
 *   'conj' e chama a funcao correspondente indicada pela operacao 'op'.
 */
void analisa_add_sub(char op, int *conj, int *tam) {

  int num = 0;
  scanf("%d", &num);
  if (op == '+') {
    *tam = adicao(conj, *tam, num);
  } else {
    *tam = subtracao(conj, *tam, num);
  }
}

/* Funcao: analisa_operacao
 *
 * Parametros:
 *     conj1: vetor contendo o conjunto de entrada do primeiro operando
 *     conj2: vetor contendo o conjunto de entrada do segundo operando
 *      tam1: tamanho do conjunto 'conj1'
 *      tam2: tamanho do conjunto 'conj2'
 *     nome1: nome do primeiro conjunto. valores: 'A' ou 'B'
 *     nome2: nome do segundo conjunto. valores: o inverso de 'nome1'
 *
 * Retorno:
 *   Se a operacao for sobre modificar 1 conjunto (+=, -=, =), entao 'conj1' e
 *   alterado com os novos valores assim como 'tam1' para refletir o novo
 *   tamanho. Se for qualquer outra operacao, nenhum dos conjuntos de entrada
 *   sao modificados.
 *   Nao ha retorno da funcao.
 *
 * Descricao:
 *   Le da entrada padrao qual operacao deve ser realizada e chama a funcao
 *   correspondente. Essa funcao analiza todas as operacoes menos a de pertence,
 *   pois assume que as operacoes sao uma das que comecam com a definicao de um
 *   conjunto, e qual o primeiro conjunto e indicado pelo 'conj1', sendo 'conj2'
 *   o segundo conjunto. Todas as operacoes, com excessao do pertence 'e'
 *   comecam com um conjunto, seguido da operacao (com excessao da de impressao)
 *   e o segundo conjunto.
 *   Ela le da entrada padrao a operacao, chama as funcoes correspondente de
 *   cada operacao e no final imprime o resultado. Para operacoes sobre um unico
 *   conjunto, o resultado a ser impresso e o proprio conjunto 'conj1'. Para
 *   operacoes sobre os dois conjuntos, o resultado a ser impresso esta em um
 *   conjunto novo 'conjRes' e o nome a ser impresso e a operacao com os
 *   conjuntos na ordem dada, assim como na entrada.
 */
void analisa_operacao(int *conj1, int *conj2, int *tam1, int *tam2, char nome1,
                      char nome2) {

  char nomeRes[20] = "\0";
  int tamRes = 0;
  int *conjRes = NULL;

  int C[CONJ_TAM];
  int tam_C = 0;

  scanf("%*[\t ]");

  char b[20] = "\0";
  scanf("%19[-=+cu^\\]", b);
  char op = b[0];

  switch (op) {
  case '+':
  case '-':
    analisa_add_sub(op, conj1, tam1);
    break;
  case '=':
    analisa_atribuicao(conj1, tam1);
    break;
  case 'u':
    tam_C = uniao(C, conj1, conj2, *tam1, *tam2);
    break;
  case '^':
    tam_C = intersecao(C, conj1, conj2, *tam1, *tam2);
    break;
  case '\\':
    tam_C = diferenca(C, conj1, conj2, *tam1, *tam2);
    break;
  case 'c':
    if (0 == contido(conj1, conj2, *tam1, *tam2)) {
      printf("falso\n");
    } else {
      printf("verdadeiro\n");
    }
    return;
  }

  if (op == '+' || op == '-' || op == '=' || op == '\0') {
    conjRes = conj1;
    tamRes = *tam1;
    nomeRes[0] = nome1;
    nomeRes[1] = '\0';
  }

  if (op == 'c' || op == 'u' || op == '^' || op == '\\') {
    conjRes = C;
    tamRes = tam_C;
    sprintf(nomeRes, "%c %c %c", nome1, op, nome2);
  }

  imprime_conjunto(conjRes, tamRes, nomeRes);
}

/* Funcao: analisa_pertence
 *
 * Parametros:
 *   palavra: valor ja lido da entrada, que sera analizado novamente, deve
 *            conter o numero a ser realizado a operacao de pertence.
 *         A: vetor contendo o conjunto de nome 'A'
 *         B: vetor contendo o conjunto de nome 'B'
 *     tam_A: tamanho do conjunto 'A'
 *     tam_B: tamanho do conjunto 'B'
 *
 * Retorno:
 *   Nao ha retorno da funcao.
 *
 * Descricao:
 *   Le da entrada padrao o conjunto a se aplicar a funcao pertente e tambem le
 *   o numero a ser utillizado a partir da string 'palavra'. Ao final ela
 *   imprime o resultado da operacao.
 */
void analisa_pertence(char *palavra, int *A, int *B, int tam_A, int tam_B) {

  int res = 0;
  int num = 0;
  char c = '\0';

  sscanf(palavra, "%d", &num);
  scanf(" e %c", &c);
  if (c == 'A') {
    res = pertence(A, tam_A, num);
  } else {
    res = pertence(B, tam_B, num);
  }
  if (res == 0) {
    printf("falso\n");
  } else {
    printf("verdadeiro\n");
  }

}

/* Funcao: main
 *
 * Descricao:
 *   Esse programa le as operacoes sobre os conjuntos 'A' e 'B', uma por linha e
 *   as realiza em ordem. Os conjuntos estao inicialmente vazios.
 *
 *   A logica da main e a seguinte. Ler da entrada padrao  a primeira palavra de
 *   cada linha, o que indica se uma operacao comeca com a letra de um conjunto
 *   ('A' ou 'B'), e o comando 'q' para terminar o programa ou a operacao de
 *   pertence, que comeca com um numero. Apos ela chama funcoes para cada um
 *   desses 3 tipos (ou termina o programa) e antes de ler uma nova linha, le da
 *   entrada padrao o resto da linha que nao tenha sido lido.
 */
int main() {
  char palavra[20] = "\0";

  int A[CONJ_TAM];
  int B[CONJ_TAM];
  int tam_A = 0;
  int tam_B = 0;

  while (EOF != scanf("%19s", palavra)) {
    char op = palavra[0];
    switch (op) {
    case 'A':
      analisa_operacao(A, B, &tam_A, &tam_B, 'A', 'B');
      break;
    case 'B':
      analisa_operacao(B, A, &tam_B, &tam_A, 'B', 'A');
      break;
    case 'q':
      return 0;
    default:
      analisa_pertence(palavra, A, B, tam_A, tam_B);
    }
    scanf("%*[^\n]\n");
  }
  return 0;
}
