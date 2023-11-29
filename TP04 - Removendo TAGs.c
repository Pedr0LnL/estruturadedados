#include <stdio.h>

int main() {
    FILE *arquivo_entrada, *arquivo_saida;
    char caractere;

    // Abre o arquivo de entrada
    arquivo_entrada = fopen("arquivo.html", "r");

    // Verifica se o arquivo foi aberto corretamente
    if (arquivo_entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    // Abre o arquivo de saída
    arquivo_saida = fopen("saida.txt", "w");

    // Verifica se o arquivo foi aberto corretamente
    if (arquivo_saida == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        return 1;
    }

    // Processa o arquivo
    int dentro_da_tag = 0; // Flag para indicar se estamos dentro de uma tag HTML

    while ((caractere = fgetc(arquivo_entrada)) != EOF) {
        if (caractere == '<') {
            dentro_da_tag = 1;
        } else if (caractere == '>') {
            dentro_da_tag = 0;
        } else if (!dentro_da_tag) {
            fputc(caractere, arquivo_saida);
        }
    }

    // Fecha os arquivos
    fclose(arquivo_entrada);
    fclose(arquivo_saida);

    printf("Tags HTML removidas com sucesso.\n");

    return 0;
}

