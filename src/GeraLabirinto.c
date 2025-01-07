#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gerarCaverna(char *filename, int linhas, int colunas, int pontos_vida) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Erro ao criar arquivo!\n");
        return;
    }

    fprintf(file, "%d %d %d\n", linhas, colunas, pontos_vida);

    srand(time(NULL));

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (i == 0 && j == 0) {
                fprintf(file, "F ");
            } else if (i == linhas - 1 && j == colunas - 1) {
                fprintf(file, "I ");
            } else {
                int valor = (rand() % 41) - 20; // Valores entre -20 e +20
                fprintf(file, "%d ", valor);
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Arquivo '%s' gerado com sucesso!\n", filename);
}

int main() {
    gerarCaverna("../lib/caverna_aleatoria.txt", 5, 5, 50);
    return 0;
}