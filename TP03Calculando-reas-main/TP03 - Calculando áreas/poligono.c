#include "poligono.h"
#include "ponto.h"

float calcularArea(Ponto* vertices, int numVertices) {
    float area = 0.0;
    for (int i = 0; i < numVertices; i++) {
        int j = (i + 1) % numVertices;
        area += (vertices[i].X * vertices[j].Y) - (vertices[i].Y * vertices[j].X);
    }
    return area / 2.0;
}
