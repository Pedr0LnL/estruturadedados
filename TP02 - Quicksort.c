#include <stdio.h>
#include <string.h>

void trocar(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}

int particionar(char **arr, int baixo, int alto) {
    char *pivot = arr[alto];
    int i = baixo - 1;

    int j;
    for (j = baixo; j <= alto - 1; j++) {
        if (strcmp(arr[j], pivot) < 0) {
            i++;
            trocar(&arr[i], &arr[j]);
        }
    }
    trocar(&arr[i + 1], &arr[alto]);

    return i + 1;
}

void quicksort(char **arr, int baixo, int alto) {
    if (baixo < alto) {
        int pi = particionar(arr, baixo, alto);

        quicksort(arr, baixo, pi - 1);
        quicksort(arr, pi + 1, alto);
    }
}

int main() {
    char *arr[20] = {"maca", "banana", "pera", "uva", "laranja", "abacaxi", "limao", "manga", "abacate", "kiwi",
                     "cereja", "morango", "pessego", "goiaba", "melancia", "framboesa", "amora", "caqui", "figo", "papaya"};
    int tamanho = sizeof(arr) / sizeof(arr[0]);

    quicksort(arr, 0, tamanho - 1);

    // Imprimir o vetor ordenado
    int i;
    for (i = 0; i < tamanho; i++) {
        printf("%s ", arr[i]);
    }

    return 0;
}

