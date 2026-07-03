#ifndef IMAGENS_H
#define IMAGENS_H
#define TAM_ICONE 32

#include <string>

using namespace std;

// Constantes
const int MAX_LIN = 1024;
const int MAX_COL = 1024;

// Tipo de imagem
typedef int tImagem[MAX_LIN][MAX_COL];

// Funcoes de leitura e escrita e verificacao
int carregaPGM(string nome, tImagem img, int *col, int *lin, int *tons);
int salvaPGM(string nome, tImagem img, int col, int lin, int tons);
int lerInteiro(string mensagem);

// Funcoes de processamento
int clarear_escurecerPGM(tImagem img, int col, int lin, int valor, int tons);
int binPGM(tImagem img, int col, int lin, int tons, int limiar);

int esquerdaPGM(tImagem img, int *lin, int *col);
int direitaPGM(tImagem img, int *lin, int *col);
int verticalPGM(tImagem img, int lin, int col);
int horizontalPGM(tImagem img, int lin, int col);

int negativoPGM(tImagem img, int lin, int col, int tons);
int passabaixaPGM(tImagem img, int lin, int col);
int escurecerbordaPGM(tImagem img, int lin, int col, int fator, int decremento);
int iconizarPGM(tImagem img, int *lin, int *col);

int passabaixainterativoPGM(tImagem img, int lin, int col);
int espelhamentoDiagonalPGM(tImagem img, int *lin, int *col);

int redimensionamentoPGM(tImagem img, int *lin, int *col);
int recortePGM(tImagem img, int *lin, int *col);

#endif