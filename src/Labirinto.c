#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "Labirinto.h"

#define TAM_BUFFER 32

// Lê as informações iniciais do arquivo (linhas, colunas e pontos de vida iniciais)
void Get_infos(FILE* arquivo, int* linhas, int* colunas, int* pts_vida) {
    fscanf(arquivo, "%d %d %d", linhas, colunas, pts_vida);
}

// Aloca dinamicamente a memória para o labirinto (uma matriz de estruturas "caverna")
labirinto Alocar_Labirinto(int linhas, int colunas) {
    labirinto tabuleiro = (labirinto)malloc(linhas * sizeof(caverna*));
    for (int i = 0; i < linhas; i++) {
        tabuleiro[i] = (caverna*)malloc(colunas * sizeof(caverna));
    }
    return tabuleiro;
}

// Lê o conteúdo do arquivo e inicializa a matriz do labirinto com base nas células descritas
void ler_arquivo(FILE* arquivo, labirinto tabuleiro, int max_linhas, int max_colunas, estudante *cdc, cave_infos *infos) {
    char buffer[TAM_BUFFER];
    char matriz[max_linhas][max_colunas][TAM_BUFFER];
    int linhas = 0, colunas = 0;

    // Lê cada linha do arquivo e divide os valores por espaços
    while (fgets(buffer, TAM_BUFFER, arquivo) != NULL && linhas <= max_linhas) {
        colunas = 0;
        char *token = strtok(buffer, " \n");

        // Preenche a matriz com os tokens da linha
        while (token != NULL && colunas < max_colunas) {
            strcpy(matriz[linhas - 1][colunas++], token);
            token = strtok(NULL, " \n");
        }

        linhas++;
    }

    // Inicializa o tabuleiro com os valores da matriz lida
    for (int i = 0; i < linhas - 1; i++) {
        for (int j = 0; j < colunas; j++) {
            // Define os atributos de cada célula com base no valor lido
            if (strcmp(matriz[i][j], "0") == 0) {
                tabuleiro[i][j].isstart = false;
                tabuleiro[i][j].isEnd = false;
                tabuleiro[i][j].action = 0;
                tabuleiro[i][j].isStudent = false;
            } else if (strcmp(matriz[i][j], "-10") == 0) {
                tabuleiro[i][j].action = -10;
                tabuleiro[i][j].isStudent = false;
            } else if (strcmp(matriz[i][j], "-20") == 0) {
                tabuleiro[i][j].action = -20;
                tabuleiro[i][j].isStudent = false;
            } else if (strcmp(matriz[i][j], "+20") == 0) {
                tabuleiro[i][j].action = 20;
                tabuleiro[i][j].isStudent = false;
            } else if (strcmp(matriz[i][j], "I") == 0) {
                tabuleiro[i][j].isstart = true;
                tabuleiro[i][j].isStudent = true;
                cdc->linha = i;
                cdc->coluna = j;
            } else if (strcmp(matriz[i][j], "F") == 0) {
                tabuleiro[i][j].isEnd = true;
                infos->linhaFim = i;
                infos->coluna_fim = j;
            }
        }
    }
}

// Libera a memória alocada para o labirinto
void Destrutor_Labirinto(labirinto tabuleiro, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(tabuleiro[i]);
    }
    free(tabuleiro);
}

// Imprime os valores de peso do labirinto (útil para depuração)
void Imprimir_Labirinto(labirinto tabuleiro, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d ", tabuleiro[i][j].peso);
        }
        printf("\n");
    }
}

// Processa o arquivo para criar e inicializar o labirinto
labirinto Processar_Arquivo(FILE* arquivo, int linhas, int colunas, estudante *cdc, cave_infos *infos) {
    labirinto tabuleiro = Alocar_Labirinto(linhas, colunas);
    ler_arquivo(arquivo, tabuleiro, linhas, colunas, cdc, infos);
    return tabuleiro;
}

// Inicializa os atributos do estudante
void Criar_Estudante(int vida, estudante *cdc) {
    cdc->vida = vida;
    cdc->isAtEndPoint = false;
}
