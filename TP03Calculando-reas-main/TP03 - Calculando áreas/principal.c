#include <stdio.h>
#include "poligono.h"

int main() {
    int numVertices, i;

    // Abrir o arquivo para leitura
    FILE *file = fopen("vertices.txt", "r");

    // Verificar se o arquivo foi aberto corretamente
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Ler o número de vértices
    fscanf(file, "%d", &numVertices);

    // Criar um array de pontos
    Ponto vertices[numVertices];

    // Ler as coordenadas dos vértices
    for (i = 0; i < numVertices; i++) {
        float x, y;
        fscanf(file, "%f %f", &x, &y);
        vertices[i] = criarPonto(x, y);
    }

    // Fechar o arquivo
    fclose(file);

    // Calcular a área
    float area = calcularArea(vertices, numVertices);

    // Se a área for negativa, inverter o sinal
    if (area < 0) {
        area = -area;
    }

    // Exibir a área
    printf("A área do polígono é %.2f\n", area);

    return 0;
}
