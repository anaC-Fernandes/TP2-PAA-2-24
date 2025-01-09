#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "Labirinto.h"

#define TAM_BUFFER 32

void get_infos(FILE* arquivo, int* linhas, int* colunas, int* pts_vida) {
    fscanf(arquivo, "%d %d %d", linhas, colunas, pts_vida);
}

labirinto Alocar_Labirinto(int linhas, int colunas) {
    labirinto tabuleiro = (labirinto)malloc(linhas * sizeof(caverna*));
    for (int i = 0; i < linhas; i++) {
        tabuleiro[i] = (caverna*)malloc(colunas * sizeof(caverna));
    }
    return tabuleiro;
}

void ler_arquivo(FILE* arquivo, labirinto tabuleiro, int max_linhas, int max_colunas) {

    char buffer[TAM_BUFFER];
    char matriz[max_linhas][max_colunas][TAM_BUFFER];
    int linhas = 0, colunas = 0;

    // Ler as linhas do arquivo
    while (fgets(buffer, TAM_BUFFER, arquivo) != NULL && linhas <= max_linhas ) {
        // Ignorar a primeira linha
        //if (linhas == 0) {
        //    linhas++;
        //    continue;
        //}

        colunas = 0;
        char *token = strtok(buffer, " \n");

        while (token != NULL && colunas < max_colunas) {
            strcpy(matriz[linhas-1][colunas++], token); // Armazena o token como string
            token = strtok(NULL, " \n");
        }

        linhas++;
    }

    // Exibir a matriz lida
    printf("Matriz lida (sem a primeira linha):\n");
    for (int i = 0; i < linhas - 1 ; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%s ", matriz[i][j]);
            if (strcmp(matriz[i][j], "0") == 0) {
                tabuleiro[i][j].isstart = false;
                tabuleiro[i][j].isend = false;
                tabuleiro[i][j].action = 0;
                tabuleiro[i][j].value[0] = '0';
            } 
            else if (strcmp(matriz[i][j], "-10") == 0) {
                tabuleiro[i][j].isstart = false;
                tabuleiro[i][j].isend = false;
                tabuleiro[i][j].action = -10;
                strcpy(tabuleiro[i][j].value, "-10");
            }
            else if (strcmp(matriz[i][j], "-20") == 0) {
                tabuleiro[i][j].isstart = false;
                tabuleiro[i][j].isend = false;
                tabuleiro[i][j].action = -20;
                strcpy(tabuleiro[i][j].value, "-20");
            }
            else if (strcmp(matriz[i][j], "+20") == 0) {
                tabuleiro[i][j].isstart = false;
                tabuleiro[i][j].isend = false;
                tabuleiro[i][j].action = +20;
                strcpy(tabuleiro[i][j].value, "+20");
            }
            else if (strcmp(matriz[i][j], "I") == 0) {
                tabuleiro[i][j].isstart = true;
                tabuleiro[i][j].isend = false;
                tabuleiro[i][j].action = 0;
                strcpy(tabuleiro[i][j].value, "I");
            }
            else if (strcmp(matriz[i][j], "F") == 0) {
                tabuleiro[i][j].isstart = false;
                tabuleiro[i][j].isend = true;
                tabuleiro[i][j].action = 0;
                strcpy(tabuleiro[i][j].value, "F");
            }
        }
        printf("\n");
    }
}

void Destrutor_Labirinto(labirinto tabuleiro, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(tabuleiro[i]);
    }
    free(tabuleiro);
}

void Imprimir_Labirinto(labirinto tabuleiro, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d ", tabuleiro[i][j].action);
        }
        printf("\n");
    }
}

labirinto Processar_Arquivo(FILE* arquivo, int linhas, int colunas) {
    labirinto tabuleiro = Alocar_Labirinto(linhas, colunas);
    ler_arquivo(arquivo,tabuleiro, linhas, colunas);
    return tabuleiro;
}