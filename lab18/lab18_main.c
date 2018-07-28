/* Include para fazer o programar dormir por nanosegundos */
#if defined(__linux__)
#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199309L
#include <time.h>

/*
 * Tempo em ns entre chamadas para o print_sudoku
 * O tempo pode ser modificado. Esse arquivo nao sera submetido.
 * Este tempo nao modifica a solucao nem a resposta
 * Valores: 0L - 999999999L
 */
unsigned long int tempo_ns = 100000000L;
#endif


#include <stdio.h>
#include <stdlib.h>

/* Lista de Cores e formatacao usados */
static const char color_reset[] = "\x1b[0m";
static const char color_sep[] = "\x1b[0;34;44m";
static const char color_sep2[] = "\x1b[0;36;46m";
static const char color_input[] = "\x1b[0;37;40m";
static const char color_player[] = "\x1b[0;30;47m";
static const char color_wrong[] = "\x1b[0;37;41m";
static const char color_change[] = "\x1b[0;30;43m";

/* Biliotecas em uso somente apenas para Linux e Mac OSX */
#if defined(__linux__) || defined(__APPLE__)
#include <string.h>
#include <termios.h>
#include <unistd.h>
#endif

int TTY = -1;
/* Verifica e habilita cores no terminal */
int enable_colors() {
  if (TTY < 0) {
#if defined(__linux__) || defined(__APPLE__)
    TTY = isatty(STDOUT_FILENO) && isatty(STDIN_FILENO);
#else
    TTY = 0;
#endif
  }
  return TTY;
}

/* Limpa a tela do terminal */
void clearScreen() {
#if defined(__linux__) || defined(__APPLE__)
  if (enable_colors()) {
    fputs("\x1b[0m\x1b[2J\x1b[1;1H", stdout);
  }
#endif
}

void gotoScreen(int x, int y) {
#if defined(__linux__) || defined(__APPLE__)
  if (enable_colors()) {
    fprintf(stdout, "\x1b[%d;%dH", x, y);
  }
#endif
}

/* Configura o terminal para enviar os caracteres sem enter e sem monstra-los na
 * tela */
#if defined(__linux__) || defined(__APPLE__)
struct termios tty_settings;
#endif
void enable_getch() {
#if defined(__linux__) || defined(__APPLE__)
  if (enable_colors()) {
    struct termios newattr;
    tcgetattr(STDIN_FILENO, &tty_settings);
    tcgetattr(STDIN_FILENO, &newattr);
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
  }
#endif
}
/* Desativa configuracao especial do terminal */
void disable_getch() {
#if defined(__linux__) || defined(__APPLE__)
  if (enable_colors()) {
    tcsetattr(STDIN_FILENO, TCSANOW, &tty_settings);
  }
#endif
}

/* Imprime cores e formatacao de texto */
void printc(const char *color) {
#if defined(__linux__) || defined(__APPLE__)
  if (enable_colors()) {
    fputs(color, stdout);
  }
#endif
}

#define MAX 9
/* Funcoes implementadas pelo aluno */
int resolve(int resposta[MAX][MAX]);

/* Tabuleiro original */
int original[MAX][MAX];

#if defined(__linux__) || defined(__APPLE__)
int ultima[MAX][MAX];
#endif

/* Imprime o numero de um mostro */
void print_pos(int v, int x, int y) {
#if defined(__linux__) || defined(__APPLE__)
  if (enable_colors()) {
    if (ultima[x][y] != v) {
      printc(color_change);
      ultima[x][y] = v;
      fputc(' ', stdout);
      fputc('0' + v, stdout);
      fputc(' ', stdout);
      return;
    } else if (original[x][y] > 0) {
      if (original[x][y] != v) {
        printc(color_wrong);
      } else {
        printc(color_input);
      }
    } else {
      printc(color_player);
    }
  }
#endif
  fputc(' ', stdout);
  if (v > 0)
    fputc('0' + v, stdout);
  else
    fputc(' ', stdout);
  fputc(' ', stdout);
}

void print_hline(const char *color2) {
  printc(color_sep);
  fputs("-", stdout);
  printc(color2);
  fputs("-----------", stdout);
  printc(color_sep);
  fputs("-", stdout);
  printc(color2);
  fputs("-----------", stdout);
  printc(color_sep);
  fputs("-", stdout);
  printc(color2);
  fputs("-----------", stdout);
  printc(color_sep);
  fputs("-\n", stdout);
}

/* Imprime valores de cada turno */
void _print_sudoku(int resposta[MAX][MAX]) {
  int i;
  clearScreen();
  for (i = 0; i < MAX; i++) {
    int j;
    if (!(i % 3)) {
      print_hline(color_sep);
    } else {
      print_hline(color_sep2);
    }
    for (j = 0; j < MAX; j++) {
      if (!(j % 3)) {
        printc(color_sep);
      } else {
        printc(color_sep2);
      }
      fputc('|', stdout);
      print_pos(resposta[i][j], i, j);
    }
    printc(color_sep);
    fputc('|', stdout);
    printc(color_reset);
    fputc('\n', stdout);
  }
  print_hline(color_sep);
  printc(color_reset);
  fflush(stdout);
}
void print_sudoku(int resposta[MAX][MAX]) {
#if defined(__linux__) || defined(__APPLE__)
  if (enable_colors()) {
    _print_sudoku(resposta);
#if defined(__linux__)
    {
      struct timespec s;
      s.tv_sec = 0;
      s.tv_nsec = tempo_ns;
      nanosleep(&s, NULL);
    }
#endif
  }
#endif
}

int main() {
  int resposta[MAX][MAX];

  enable_getch();
  clearScreen();

  {
    int i;
    for (i = 0; i < MAX; i++) {
      int j;
      for (j = 0; j < MAX; j++) {
        original[i][j] = -2;
        resposta[i][j] = -1;

#if defined(__linux__) || defined(__APPLE__)
        ultima[i][j] = -1;
#endif
      }
    }
  }

  print_sudoku(resposta);
  {
    int i;
    for (i = 0; i < MAX; i++) {
      int j;
      for (j = 0; j < MAX; j++) {
        char c = 0;
        while ((c = fgetc(stdin)) < '0' || c > '9')
          ;
        original[i][j] = c - '0';
        resposta[i][j] = original[i][j];
        if (enable_colors()) {
          print_sudoku(resposta);
        }
      }
    }
  }
  _print_sudoku(resposta);

  {
    int r;
    r = resolve(resposta);
    if (!!r) {
      _print_sudoku(resposta);
    } else {
      printf("Nao foi encontrada uma solucao.\n");
    }
  }
  disable_getch();

  return 0;
}
