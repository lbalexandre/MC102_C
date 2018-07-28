#include <stdio.h>
#include <stdlib.h>

/* Lista de Cores e formatacao usados */
static const char color_reset[] = "\x1b[0m";
static const char color_bold[] = "\x1b[0;1m";
static const char color_sep[] = "\x1b[0;36m";
static const char color_black[] = "\x1b[0;30m";
static const char color_grass[] = "\x1b[0;32m";
static const char color_player[] = "\x1b[0;1m";
static const char *colors_list[] = {"\x1b[0;31m", "\x1b[0;33m", "\x1b[0;34m",
                                    "\x1b[0;35m", "\x1b[0;36m"};

/* Biliotecas em uso somente apenas para Linux e Mac OSX */
#if defined(__linux__) || defined(__APPLE__)
#include <unistd.h>
#include <termios.h>
#include <time.h>
#include <string.h>
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
    fputs("\x1b[2J\x1b[1;1H", stdout);
  }
  #endif
}

/* Configura o terminal para enviar os caracteres sem enter e sem monstra-los na tela */
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

#define MAX 20
#define MONSTROS 151

/* Funcoes implementadas pelo aluno */
void busca(int tab[MAX][MAX], int pos[2]);
void visiveis(int tab[MAX][MAX], int v[8]);
void proximos(int tab[MAX][MAX], int p[MONSTROS]);
int movimenta(int tab[MAX][MAX], int desloca[2]);
int captura(int capturados[MONSTROS], int especie);

/* Imprime o numero de um mostro */
void print_monstro(int I) {
  if (I) {
    printc(
        colors_list[I / (MONSTROS /
                         (sizeof(colors_list) / sizeof(colors_list[0]) - 1))]);
  } else {
    printc(color_grass);
  }
  printf("%03d", I);
}

/* Imprime mapa de monstros visiveis */
void print_vis(int tab[MAX][MAX]) {
  int vis[8];
  for (int i = 0; i < 8; i++)
    vis[i] = 0;
  visiveis(tab, vis);
  int c = 0;
  for (int i = 0; i < 8; i++) {
    print_monstro(vis[i]);
    c++;

    if (i == 3) {
      printc(color_player);
      printf(" .J. ");
      c++;
    } else if (c % 3) {
      printf(" ");
    } else {
      printf("\n");
    }
  }
  printc(color_reset);
}

/* Imprime lista de monstros proximos */
void print_prox(int tab[MAX][MAX]) {
  int prox[MONSTROS];
  for (int i = 0; i < MONSTROS; i++)
    prox[i] = 0;
  proximos(tab, prox);
  printc(color_reset);
  printf("Proximos: ");
  for (int i = 0; i < MONSTROS; i++)
    if (prox[i]) {
      print_monstro(i + 1);
      printc(color_reset);
      printf(", ");
    }
  printf("\n");
}

/* Imprime valores de cada turno */
void print_turno(int tab[MAX][MAX], int passos, int experiencia,
                 int restantes) {
  print_vis(tab);
  printc(color_black);
  printf("-----------\n");
  print_prox(tab);
  printf("Passos: %d\n", passos);
  printf("Experiencia: %d\n", experiencia);
  printf("Monstros Restantes: %d\n", restantes);
  fflush(stdout);
}

int main(int argc, char **argv) {
  int capturados[MONSTROS]; // Quantidade de capturados para cada especie
  int tab[MAX][MAX];
  int restantes = 0;
  int experiencia = 0;
  int passos = 0;

  for (int i = 0; i < MONSTROS; i++) // Limpa vetor de capturados
    capturados[i] = 0;

  #if defined(__linux__) || defined(__APPLE__)
  if (argc > 1 && !strcmp(argv[1],"play")) { // Definir tabuleiro aleatoriamente
    srand(time(NULL));

    restantes = 0;
    for (int i = 0; i < MAX; i++) {
      for (int j = 0; j < MAX; j++) {
        tab[i][j] = rand() % (2 * MONSTROS);
        if (tab[i][j] >= (MONSTROS + 80)) {
          tab[i][j] = 0;
        } else if (tab[i][j] >= MONSTROS) {
          tab[i][j] = 1;
          restantes++;
        } else if (tab[i][j] > 0) {
          restantes++;
        }
      }
    }
    if (tab[MAX / 2][MAX / 2]) restantes--;
    tab[MAX / 2][MAX / 2] = -1;
  }
  else
  #endif

  for (int i = 0; i < MAX; i++) {
    for (int j = 0; j < MAX; j++) {
      if (scanf("%d", &tab[i][j]) != 1) {
        printf("Erro na leitura do tabuleiro\n");
        return 1;
      }
      if (tab[i][j] > 0)
        restantes++;
    }
  }

  enable_getch(); // Configura terminal

  clearScreen();
  printc(color_sep);
  printf("===========\n");
  print_turno(tab, passos, experiencia, restantes);
  while (1) {
    int op = fgetc(stdin);
    int desloca[2];
    switch (op) {
    case EOF:
    case 'X':
    case 'x':
      printc(color_sep);
      printf("===========\n");
      printc(color_bold);
      printf("Jogador acabou com %d de experiencia\n", experiencia);
      printc(color_reset);
      for (int i = 0; i < MONSTROS; i++) {
        if (!capturados[i])
          continue;
        printf("%d * ", capturados[i]);
        print_monstro(i + 1);
        printc(color_reset);
        printf(", ");
      }
      printf("\n");
      disable_getch(); //Volta o terminal as configuracoes originais
      return 0;
    case 'A': // Seta para cima
    case '^':
      desloca[0] = -1;
      desloca[1] = 0;
      break;
    case 'B': // Seta para baixo
    case 'V':
    case 'v':
      desloca[0] = 1;
      desloca[1] = 0;
      break;
    case 'C': // Seta para direita
    case '>':
      desloca[0] = 0;
      desloca[1] = 1;
      break;
    case 'D': // Seta para esqueda
    case '<':
      desloca[0] = 0;
      desloca[1] = -1;
      break;
    default:
      continue;
    }

    clearScreen();
    int especie = movimenta(tab, desloca);
    passos++;
    printc(color_sep);
    printf("===========");
    if (especie != 0) {
      restantes--;
      printc(color_bold);
      fputc(' ', stdout);
      print_monstro(especie);
      if (captura(capturados, especie)) {
        experiencia += especie;
        fputs(" capturado", stdout);
      } else {
        fputs(" fugiu", stdout);
      }
    }
    printf("\n");
    printc(color_reset);
    print_turno(tab, passos, experiencia, restantes);
  }
}
