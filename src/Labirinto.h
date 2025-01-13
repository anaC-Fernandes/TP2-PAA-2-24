#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



typedef struct cell {
    int action;     // ação
    int peso;       // peso
    char value[4];     // valor
    bool isstart;   // Começo
    bool isEnd;     // Fim
    bool isStudent;  // Estudante
    bool wasCalculated; // foi Calculado
} caverna;

typedef struct estudante {
    int linha,coluna;
    int vida;
    bool isAtEndPoint;
}estudante;

typedef struct cave_infos {
    int linhaFim, coluna_fim;
    int ordem[2];
}cave_infos;

typedef caverna** labirinto;

labirinto Alocar_Labirinto(int linhas, int colunas);
void Destrutor_Labirinto(labirinto tabuleiro, int linhas);
void Imprimir_Labirinto(labirinto tabuleiro, int linhas, int colunas);
labirinto Processar_Arquivo(FILE* arquivo, int linhas, int colunas,  estudante *cdc, cave_infos *infos);
void Get_infos(FILE* arquivo, int* linhas, int* colunas, int* pts_vida);
void Criar_Estudante(int vida, estudante *cdc);

