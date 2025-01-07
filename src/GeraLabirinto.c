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

    // Determinar posições de F e I
    int posF_x = rand() % (linhas - 1);
    int posF_y = rand() % (colunas - 1);
    int posI_x = posF_x + 1 + rand() % (linhas - posF_x - 1);
    int posI_y = posF_y + 1 + rand() % (colunas - posF_y - 1);

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (i == posF_x && j == posF_y) {
                fprintf(file, "F ");
            } else if (i == posI_x && j == posI_y) {
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