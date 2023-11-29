#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

typedef struct {
    char nome[100];
    char telefone[15];
    char curso[100];
    float nota1;
    float nota2;
} Aluno;

int main() {
    FILE *entrada, *saida;
    char linha[MAX_LINE_LENGTH];

    entrada = fopen("DadosEntrada.csv", "r");
    saida = fopen("SituacaoFinal.csv", "w");

    if (entrada == NULL || saida == NULL) {
        perror("Erro ao abrir arquivos");
        exit(EXIT_FAILURE);
    }

    fprintf(saida, "Nome,Nota Media,Situacao\n");

    while (fgets(linha, sizeof(linha), entrada) != NULL) {
        Aluno aluno;
        float media;
        char situacao[20];

        // Separar os campos da linha
        char *token = strtok(linha, ",");
        strcpy(aluno.nome, token);

        token = strtok(NULL, ",");
        strcpy(aluno.telefone, token);

        token = strtok(NULL, ",");
        strcpy(aluno.curso, token);

        token = strtok(NULL, ",");
        aluno.nota1 = atof(token);

        token = strtok(NULL, ",");
        aluno.nota2 = atof(token);

        // Calcular a média
        media = (aluno.nota1 + aluno.nota2) / 2;

        // Determinar a situação
        if (media >= 7.0) {
            strcpy(situacao, "APROVADO");
        } else {
            strcpy(situacao, "REPROVADO");
        }

        // Escrever no arquivo de saída
        fprintf(saida, "%s,%.2f,%s\n", aluno.nome, media, situacao);
    }

    fclose(entrada);
    fclose(saida);

    printf("Processamento concluído. Os resultados foram escritos em SituacaoFinal.csv\n");

    return 0;
}
