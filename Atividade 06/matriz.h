#ifndef MATRIZ_H
#define MATRIZ_H
#include <stdio.h>
typedef struct Celula {
    struct Celula *direita, *abaixo;
    int linha, coluna;
    float valor;
} Celula;

typedef struct {
    Celula *cabeca;
    int nlin, ncol;
} Matriz;

void inicializaMatriz(Matriz *matriz, int nlin, int ncol);
void insere(Matriz *matriz, int linha, int coluna, float valor);
void imprimeMatriz(Matriz A);
Matriz leMatriz(FILE *arquivo);
Matriz somaMatrizes(Matriz A, Matriz B);
Matriz multiplicaMatrizes(Matriz A, Matriz B);
void liberaMatriz(Matriz *matriz);

#endif
