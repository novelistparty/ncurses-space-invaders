
#ifndef SPACE_INVADERS_GAME_SPCINV_H
#define SPACE_INVADERS_GAME_SPCINV_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/time.h>

/* Constantes */

// Delay de cada frame
#define DELAY 10000

// Pontuacao por alien atingido
#define KILL_SCORE 10

// Tamanho minimo da window
#define MIN_WINX 90
#define MIN_WINY 45

// Macro para a direcao dos movimentos
#define RIGHT 1
#define LEFT -1
#define UP -2
#define DOWN 2

// Define a quantidade de lasers no jogo
#define MAX_LASERS 4

// Aonde os sfx estao
#define SFX_PATH "./spcinv/sfx/"

// Como eles sao tocados
#define SFX_COMMAND "play -q"

// Qua extensão eles usam
#define SFX_EXTENSION ".wav"

/* Definicoes e construtores */

// Struct de posicao
typedef struct position {
    int x;
    int y;
} vec2;

// Struct de area
typedef struct areas {
    int x1;
    int x2;
    int y1;
    int y2;
} area;

// Struct de componente, posicao, vivo ou morto e direcao
typedef struct components {
    vec2 pos;
    bool isAlive;
    int direction;
} component;

// Inicia o jogo e configura o ncurses
static void initGame();

// Define a posicao inicial do player
static void initPlayer();

// Inicializa a matriz dos aliens
static void initAliens();

// Inicia os lasers nas suas posicoes
static void initLasers();

// Comeca o loop do jogo
// Chama a funcao getPressedKey()
// Chama a funcao getWinSize()
// Chama as funcoes de movimento
extern void startSpaceInvaders();

// Pega a tecla pressionada no momento e manda para PRESSED_KEY
static void getPressedKey();

// Pega o tamanho da tela atual e manda para WIN_SIZE
static void getWinSize();

// Para o jogo, mostrando uma mensagem se ganhou
// ou nao. Para o ncurses apos isso
static void gameOver(bool winner);

// Movimenta o player, acoes baseadas em PRESSED_KEY
// A posicao eh baseada em PLAYER_POS
static void playerMovement();

// Movimenta os aliens
// Detecta colisoes com a parede e modifica o ALIENS_DIRECTION
static void aliensMovement();

// Detecta colisoes do player com os aliens ou lasers dos aliens
static void playerLife();

// Verifica aliens vs lasers
static void aliensLife();

// Detecta se o jogador quer atirar e chama playerLaser()
static void playerShoot();

// Desenha os tiros dos aliens
static void aliensShoot();

// Movimenta os lasers
static void playerLaser();

// Renderiza
// Chama as funcoes draw*() a cada loop
static void render();

// Desenha as bordas do jogo
// Manda o tamanho da borda para BORDER_SIZE
static void drawBorder();

// Desenha uma matriz de aliens
static void drawAliens();

// Desenha um player na posicao dada
static void drawPlayer();

// Desenha os lasers em suas posicoes
static void drawLasers();

// Movimenta um componente baseado em sua direcao se ele estiver vivo
static void moveComponent(component *comp);

// Usado para tocar um sfx
static void playSound(char *name);

// Usado para descobrir aonde o executavel esta
// Baseado em http://advancedlinuxprogramming.com/listings/chapter-7/get-exe-path.c
static void getWorkingDirectory (char* buffer, size_t size);

/* Variaveis globais */

// Tamanho da tela
vec2 WIN_SIZE;

// Area da borda
area BORDER_AREA;

// Posicao do player
vec2 PLAYER_POS;

// Posicao dos aliens
component **ALIENS;

// Posicao dos lasers
vec2 LASER_POS[MAX_LASERS];

// Diz se existe um disparo do player em andamento
bool IS_PLAYER_SHOOTING;

// Player possui vidas, que valem em colisoes com lasers
unsigned int PLAYER_LIVES;

// Score
unsigned int SCORE;

/* Aliens */
// Linhas e Colunas
unsigned int ALIENS_ROWS;
unsigned int ALIENS_COLUMNS;

// Direcao dos aliens, muda de acordo com as colisoes
int ALIENS_DIRECTION;

// Armazena o indice da fileira de aliens mais proxima do player
unsigned int LAST_ALIVE_ROW;

// Ultimo alien vivo da ultima fileira
unsigned int LAST_ALIVE_ALIEN;

// True para normal, false para gameover
bool GAME_STATUS;

// Qual tecla esta sendo pressionada no momento
int PRESSED_KEY;

// Um timer global, eh incrementado a cada loop da funcao play()
unsigned long int GLOBALTIME;

// Como a borda deve se parecer
char BORDER[1];

// Usado para estocar o diretorio atual do executavel
// 4096 é baseado no tamanho máximo de bytes que um filepath pode ter no sistema de arquivos EXT
char WORKING_DIR[4096];

// Usado para debug
#ifdef DEBUG

static void drawDebug();

#endif // DEBUG

#endif // SPACE_INVADERS_GAME_SPCINV_H
