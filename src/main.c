#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Movimento.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Digitar somente caminho \\nome_arquivo.txt\n");
        return 1;
    }
    estudante cdc;
    cave_infos infos;
    char buffer[128];

    strcpy(buffer, argv[1]);
    FILE* arquivo = fopen(buffer, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int linhas = 0, colunas = 0, pts_vida = 0;
    Get_infos(arquivo, &linhas, &colunas, &pts_vida);
    infos.ordem[0] = linhas - 1;
    infos.ordem[1] = colunas - 1;

    labirinto tabuleiro = Processar_Arquivo(arquivo, linhas, colunas, &cdc, &infos);
    Criar_Estudante(pts_vida, &cdc);
    if (Problema_valido(infos, cdc)) {
        Movimenta_estudante(tabuleiro, &cdc, infos);
    }

    Destrutor_Labirinto(tabuleiro, linhas);
    fclose(arquivo);

    
    return 0;
}
