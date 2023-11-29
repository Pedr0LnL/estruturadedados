#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>

void inicializaCabeca(Celula *cabeca)
{
    cabeca->linha = -1;
    cabeca->coluna = -1;
    cabeca->valor = 0.0;
    cabeca->direita = cabeca;
    cabeca->abaixo = cabeca;
}

void inicializaMatriz(Matriz *matriz, int nlin, int ncol)
{
    matriz->cabeca = (Celula *)malloc(sizeof(Celula));
    if (matriz->cabeca == NULL)
    {
        perror("Erro na alocacao de memoria para a celula cabeca");
        exit(EXIT_FAILURE);
    }

    inicializaCabeca(matriz->cabeca);

    matriz->nlin = nlin;
    matriz->ncol = ncol;

    Celula *temp = matriz->cabeca;
    Celula *novaCabecaLinha;

    int i; 
    for (i = 0; i < nlin; i++)
    {
        novaCabecaLinha = (Celula *)malloc(sizeof(Celula));
        inicializaCabeca(novaCabecaLinha);
        temp->abaixo = novaCabecaLinha;
        temp = novaCabecaLinha;
    }
    temp->abaixo = matriz->cabeca;

    temp = matriz->cabeca;
    Celula *novaCabecaColuna;

    int j; 
    for (j = 0; j < ncol; j++)
    {
        novaCabecaColuna = (Celula *)malloc(sizeof(Celula));
        inicializaCabeca(novaCabecaColuna);
        temp->direita = novaCabecaColuna;
        temp = novaCabecaColuna;
    }
    temp->direita = matriz->cabeca;
}

void insere(Matriz *matriz, int linha, int coluna, float valor)
{
    Celula *novaCelula = (Celula *)malloc(sizeof(Celula));
    if (novaCelula == NULL)
    {
        perror("Erro na alocacao de memoria para a nova celula");
        exit(EXIT_FAILURE);
    }

    novaCelula->linha = linha;
    novaCelula->coluna = coluna;
    novaCelula->valor = valor;

    Celula *linhaAtual = matriz->cabeca;
    int i;
    for (i = 0; i < linha; i++)
    {
        linhaAtual = linhaAtual->abaixo;
    }

    Celula *anteriorLinha = linhaAtual;
    while (anteriorLinha->direita != linhaAtual && anteriorLinha->direita->coluna < coluna)
    {
        anteriorLinha = anteriorLinha->direita;
    }

    novaCelula->direita = anteriorLinha->direita;
    anteriorLinha->direita = novaCelula;

    Celula *colunaAtual = matriz->cabeca;
    int j;
    for (j = 0; j < coluna; j++)
    {
        colunaAtual = colunaAtual->direita;
    }

    Celula *anteriorColuna = colunaAtual;
    while (anteriorColuna->abaixo != colunaAtual && anteriorColuna->abaixo->linha < linha)
    {
        anteriorColuna = anteriorColuna->abaixo;
    }

    novaCelula->abaixo = anteriorColuna->abaixo;
    anteriorColuna->abaixo = novaCelula;
}

Matriz leMatriz(FILE *arquivo)
{
    Matriz matriz;
    int nlin, ncol, linha, coluna;
    float valor;

    if (fscanf(arquivo, "%d %d", &nlin, &ncol) != 2)
    {
        printf("Erro na leitura das dimensoes da matriz.\n");
        exit(EXIT_FAILURE);
    }

    inicializaMatriz(&matriz, nlin, ncol);

    while (fscanf(arquivo, "%d %d %f", &linha, &coluna, &valor) == 3)
    {
        insere(&matriz, linha, coluna, valor);
    }

    return matriz;
}

void imprimeMatriz(Matriz A)
{
    Celula *linhaAtual, *celulaAtual;

    int j;
    for (linhaAtual = A.cabeca->abaixo; linhaAtual != A.cabeca; linhaAtual = linhaAtual->abaixo)
    {
        celulaAtual = linhaAtual->direita;
        
        int i; 
        for (i = 1; i <= A.ncol; i++)
        {
            if (celulaAtual != linhaAtual && celulaAtual->coluna == i)
            {
                printf("%.2f ", celulaAtual->valor);
                celulaAtual = celulaAtual->direita;
            }
            else
            {
                printf("0.00 ");
            }
        }
        printf("\n");
    }
}

Matriz somaMatrizes(Matriz A, Matriz B)
{
    if (A.nlin != B.nlin || A.ncol != B.ncol)
    {
        printf("Erro: Matrizes de dimensoes diferentes.\n");
        exit(EXIT_FAILURE);
    }

    Matriz C;
    inicializaMatriz(&C, A.nlin, A.ncol);

    Celula *linhaA = A.cabeca->abaixo, *linhaB = B.cabeca->abaixo;
    while (linhaA != A.cabeca && linhaB != B.cabeca)
    {
        Celula *celulaA = linhaA->direita, *celulaB = linhaB->direita;

        while (celulaA != linhaA || celulaB != linhaB)
        {
            if (celulaA != linhaA && (celulaB == linhaB || celulaA->coluna < celulaB->coluna))
            {
                insere(&C, celulaA->linha, celulaA->coluna, celulaA->valor);
                celulaA = celulaA->direita;
            }
            else if (celulaB != linhaB && (celulaA == linhaA || celulaB->coluna < celulaA->coluna))
            {
                insere(&C, celulaB->linha, celulaB->coluna, celulaB->valor);
                celulaB = celulaB->direita;
            }
            else
            {
                insere(&C, celulaA->linha, celulaA->coluna, celulaA->valor + celulaB->valor);
                celulaA = celulaA->direita;
                celulaB = celulaB->direita;
            }
        }

        linhaA = linhaA->abaixo;
        linhaB = linhaB->abaixo;
    }

    return C;
}

Matriz multiplicaMatrizes(Matriz A, Matriz B)
{
    if (A.ncol != B.nlin)
    {
        fprintf(stderr, "Erro: As dimensoes das matrizes nao sao compativeis para multiplicacao.\n");
        exit(EXIT_FAILURE);
    }

    Matriz C;
    inicializaMatriz(&C, A.nlin, B.ncol);

    Celula *linhaA = A.cabeca->abaixo;
    while (linhaA != A.cabeca)
    {
        Celula *colunaB = B.cabeca->direita;
        while (colunaB != B.cabeca)
        {
            float soma = 0.0;

            Celula *celulaA = linhaA->direita;
            while (celulaA != linhaA)
            {
                Celula *celulaB = colunaB->abaixo;
                while (celulaB != colunaB)
                {
                    if (celulaA->coluna == celulaB->linha)
                    {
                        soma += celulaA->valor * celulaB->valor;
                    }
                    celulaB = celulaB->abaixo;
                }
                celulaA = celulaA->direita;
            }

            if (soma != 0.0)
            {
                insere(&C, linhaA->linha, colunaB->coluna, soma);
            }
            colunaB = colunaB->direita;
        }
        linhaA = linhaA->abaixo;
    }

    return C;
}

