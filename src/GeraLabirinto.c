#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000

int matriz[MAX][MAX];
int linhas, colunas;

int dfs(int x, int y, int soma) {
    if (x < 0 || y < 0 || x >= linhas || y >= colunas || matriz[x][y] == -999) {
        return 0;
    }
    if (x == linhas - 1 && y == colunas - 1) {
        return soma + matriz[x][y] > 0;
    }

    int temp = matriz[x][y];
    matriz[x][y] = -999; // Marca como visitado

    int found = dfs(x + 1, y, soma + temp) ||
                dfs(x, y + 1, soma + temp) ||
                dfs(x - 1, y, soma + temp) ||
                dfs(x, y - 1, soma + temp);

    matriz[x][y] = temp; // Desmarca

    return found;
}

void ajustarCaminho() {
    int x = 0, y = 0, soma = 0;
    while (x != linhas - 1 || y != colunas - 1) {
        soma += matriz[x][y];
        if (soma <= 0) {
            matriz[x][y] = 1 - soma;
            soma = 1;
        }
        if (x < linhas - 1 && matriz[x + 1][y] != -999) {
            x++;
        } else if (y < colunas - 1 && matriz[x][y + 1] != -999) {
            y++;
        }
    }
}

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
                matriz[i][j] = 'F';
            } else if (i == posI_x && j == posI_y) {
                matriz[i][j] = 'I';
            } else {
                matriz[i][j] = (rand() % 41) - 20; // Valores entre -20 e +20
            }
        }
    }

    // Ajustar valores para garantir caminho positivo
    if (!dfs(posF_x, posF_y, 0)) {
        ajustarCaminho();
    }

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] == 'F' || matriz[i][j] == 'I') {
                fprintf(file, "%c ", matriz[i][j]);
            } else {
                fprintf(file, "%d ", matriz[i][j]);
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Arquivo '%s' gerado com sucesso!\n", filename);
}

int main() {
    linhas = 5;
    colunas = 5;
    gerarCaverna("../lib/caverna_aleatoria.txt", linhas, colunas, 50);
    
    
    int x = 0;
    int y = 0;
    FILE *fp = NULL;
    FILE *gnupipe = NULL;
    char *GnuCommands [] = {"set title \"Grafico tempo x entrada\"", "plot 'data.tmp'"};
    clock_t comeco, fim;

    fp = fopen("data.tmp", "w");
    gnupipe = _popen("gnuplot -persist", "w");

    comeco = clock();
    gerarCaverna("../lib/caverna_aleatoria1.txt", 10, 10, 50);
    fim = clock();
    fprintf(fp, "%d %d\n", 1, (fim - comeco)/ CLOCKS_PER_SEC);
    printf("Diferenca: %d\n", (fim - comeco)/ CLOCKS_PER_SEC);

    comeco = clock();
    gerarCaverna("../lib/caverna_aleatoria2.txt", 100, 100, 50);
    fim = clock();
    fprintf(fp, "%d %d\n", 2, (fim - comeco)/ CLOCKS_PER_SEC);
    printf("Diferenca: %d\n", (fim - comeco)/ CLOCKS_PER_SEC);

    comeco = clock();
    gerarCaverna("../lib/caverna_aleatoria3.txt", 200, 100, 500);
    fim = clock();
    fprintf(fp, "%d %d\n", 3, (fim - comeco)/ CLOCKS_PER_SEC);
    printf("Diferenca: %d\n", (fim - comeco)/ CLOCKS_PER_SEC);

    comeco = clock();
    gerarCaverna("../lib/caverna_aleatoria4.txt", 500, 500, 500);
    fim = clock();
    fprintf(fp, "%d %d\n", 4, (fim - comeco)/ CLOCKS_PER_SEC);
    printf("Diferenca: %d\n", (fim - comeco)/ CLOCKS_PER_SEC);

    comeco = clock();
    
    /*for (int i=0; i<500000; i++){
        //fprintf(fp, "%d %d\n", x, y);
        printf("%d\n", i);
        x = x+1;
        y = x*x;
        
    }*/
    gerarCaverna("../lib/caverna_aleatoria5.txt", 999, 999, 5000);
    fim = clock();
    fprintf(fp, "%d %d\n", 5, (fim - comeco)/ CLOCKS_PER_SEC);
    printf("Diferenca: %d\n", (fim - comeco)/ CLOCKS_PER_SEC);

    for (int i=0; i<2; i++){
        fprintf(gnupipe, "%s\n", GnuCommands[i]);
    }

    return 0;
    
    return 0;
}