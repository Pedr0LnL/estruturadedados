#include "matriz.h"
#include <stdio.h>

int main(void) {
    Matriz A, B, C, D;
    FILE *arquivoA, *arquivoB;

    arquivoA = fopen("matrizA.txt", "r");
    if (arquivoA == NULL) {
        perror("Erro ao abrir arquivo da matriz A");
        return 1;
    }

    arquivoB = fopen("matrizB.txt", "r");
    if (arquivoB == NULL) {
        perror("Erro ao abrir arquivo da matriz B");
        fclose(arquivoA);
        return 1;
    }

    A = leMatriz(arquivoA);
    fclose(arquivoA);

    B = leMatriz(arquivoB);
    fclose(arquivoB);

    printf("Matriz A:\n");
    imprimeMatriz(A);

    printf("Matriz B:\n");
    imprimeMatriz(B);

    C = somaMatrizes(A, B);
    printf("Soma de A e B:\n");
    imprimeMatriz(C);

    D = multiplicaMatrizes(A, B);
	printf("Multiplicacao de A e B:\n");
	imprimeMatriz(D);


    return 0;
}
