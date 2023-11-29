#include <stdio.h>
#include <stdlib.h>

// Definindo a estrutura do n� da lista
typedef struct Node {
    int valor;
    struct Node* prox;
} Node;

// Fun��o para calcular a m�dia aritm�tica
float calcularMedia(Node* head) {
    int soma = 0;
    int contador = 0;
    Node* atual = head;

    // Percorre a lista e calcula a soma
    while (atual != NULL) {
        soma += atual->valor;
        contador++;
        atual = atual->prox;
    }

    // Calcula a m�dia (soma / contador)
    if (contador > 0) {
        return (float)soma / contador;
    } else {
        return 0.0; // Retorna 0 se a lista estiver vazia para evitar divis�o por zero
    }
}

// Fun��o principal para testar
int main() {
    // Cria��o da lista (exemplo)
    Node* lista = (Node*)malloc(sizeof(Node));
    lista->valor = 10;

    lista->prox = (Node*)malloc(sizeof(Node));
    lista->prox->valor = 20;

    lista->prox->prox = (Node*)malloc(sizeof(Node));
    lista->prox->prox->valor = 30;

    lista->prox->prox->prox = NULL;

    // Chama a fun��o para calcular a m�dia
    float media = calcularMedia(lista);

    // Imprime a m�dia
    printf("A media aritmetica dos elementos da lista e: %.2f\n", media);

    // Libera a mem�ria alocada para a lista
    Node* atual = lista;
    Node* proximo;
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    return 0;
}

