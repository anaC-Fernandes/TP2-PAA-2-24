#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct cell {
    int action;     // ação
    char value[4];     // valor
    bool isstart;   // eComeço
    bool isend;     // eFim
} caverna;

typedef caverna** labirinto;

labirinto Alocar_Labirinto(int linhas, int colunas);
void Destrutor_Labirinto(labirinto tabuleiro, int linhas);
void Imprimir_Labirinto(labirinto tabuleiro, int linhas, int colunas);
labirinto Processar_Arquivo(FILE* arquivo, int linhas, int colunas);
