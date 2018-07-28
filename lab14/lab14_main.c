#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int *numeros; // Vetor com elementos, pode ser ordenado ou nao.
  int elementos; // Quantidade de elementos distintos
  int capacidade; // Tamanho do vetor 'numeros' para gerenciar alocacao de memoria
} conjunto;

void imprime(conjunto *conj);
void limpa(conjunto *conj);
conjunto *novo(int capacidade);
void aumenta_capacidade(conjunto *conj, int capacidade);
void deleta(conjunto *conj);
int pertence(conjunto *conj, int num);
int contido(conjunto *conj1, conjunto *conj2);
void adicao(conjunto *conj, int num);
void subtracao(conjunto *conj, int num);
conjunto *uniao(conjunto *conj1, conjunto *conj2);
conjunto *intersecao(conjunto *conj1, conjunto *conj2);
conjunto *diferenca(conjunto *conj1, conjunto *conj2);

int cmp(const void *A, const void *B) {
  int *a = (int *)A;
  int *b = (int *)B;
  if (*a == *b) {
    printf("Dois elementos iguais: %d", *a);
  }
  return *a - *b;
}

void imprime(conjunto *conj) {
  int repetidos = 0;
  printf("{");
  if (conj->elementos>0){
    int *copia = malloc(conj->elementos*sizeof(int));
    memcpy(copia, conj->numeros, conj->elementos*sizeof(int));
    qsort(copia, conj->elementos, sizeof(int), cmp);

    printf("%d", copia[0]);
    for (int i = 1; i<conj->elementos; i++) {
      printf(", %d", copia[i]);
      repetidos += copia[i] == copia[i-1];
    }
    free(copia);
  }
  printf("}\n");

  if(repetidos)
    printf("%d numeros repetidos\n", repetidos);
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
void analisa_atribuicao(conjunto *conj) {

  int num = 0;
  conj->elementos = 0;
  scanf(" { ");
  while (0 < scanf(" %d ,", &num)) {
    adicao(conj, num);
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
void analisa_add_sub(char op, conjunto *conj) {

  int num = 0;
  scanf("%d", &num);
  if (op == '+') {
    adicao(conj, num);
  } else {
    subtracao(conj, num);
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
void analisa_operacao(conjunto *conj1, conjunto *conj2, char nome1,
                      char nome2) {

  conjunto *res = NULL;

  scanf("%*[\t ]");

  char b[20] = "\0";
  scanf("%19[-=+cu^\\]", b);
  char op = b[0];

  switch (op) {
  case '+':
  case '-':
    analisa_add_sub(op, conj1);
    break;
  case '=':
    analisa_atribuicao(conj1);
    break;
  case 'u':
    res = uniao(conj1, conj2);
    break;
  case '^':
    res = intersecao(conj1, conj2);
    break;
  case '\\':
    res = diferenca(conj1, conj2);
    break;
  case 'c':
    if (0 == contido(conj1, conj2)) {
      printf("falso\n");
    } else {
      printf("verdadeiro\n");
    }
    return;
  }

  if (op == '+' || op == '-' || op == '=' || op == '\0') {
    printf("%c = ", nome1);
    imprime(conj1);
  } else if (op == 'c' || op == 'u' || op == '^' || op == '\\') {
    printf("%c %c %c = ", nome1, op, nome2);
    imprime(res);
    deleta(res);
  }

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
void analisa_pertence(char *palavra, conjunto *A, conjunto *B) {

  int res = 0;
  int num = 0;
  char c = '\0';

  sscanf(palavra, "%d", &num);
  scanf(" e %c", &c);
  if (c == 'A') {
    res = pertence(A, num);
  } else {
    res = pertence(B, num);
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

  conjunto *A = novo(10);
  conjunto *B = novo(10);

  if (!(A && B)) {
    printf("Conjuntos nao alocados.\n");
  }

  while (palavra[0] != 'q' && EOF != scanf("%19s", palavra)) {
    char op = palavra[0];
    switch (op) {
    case 'A':
      analisa_operacao(A, B, 'A', 'B');
      break;
    case 'B':
      analisa_operacao(B, A, 'B', 'A');
      break;
    case 'q':
      break;
    default:
      analisa_pertence(palavra, A, B);
    }
    scanf("%*[^\n]\n");
  }

  deleta(B);
  deleta(A);

  return 0;
}
