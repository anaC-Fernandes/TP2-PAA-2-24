#include <stdio.h>
#include <stdlib.h>
#include "Labirinto.h"

//main de teste
/*int main(){
    estudante cdc;
    cave_infos infos;
    char buffer[128];
    //printf("Digite o caminho do arquivo: ");
    //scanf("%s", buffer);
    strcpy(buffer, "/home/gabrielbd/Codes/TP2-PAA-2-24/lib/teste.txt");
    FILE* arquivo = fopen(buffer,"r");
    int linhas = 0, colunas = 0, pts_vida = 0;
    get_infos(arquivo, &linhas, &colunas, &pts_vida);
    infos.ordem[0] = linhas - 1;
    infos.ordem[1] = colunas - 1;
    


    labirinto tabuleiro = Processar_Arquivo(arquivo,linhas,colunas, &cdc, &infos);
    Criar_Estudante(pts_vida, &cdc);
    if (problema_valido(infos, cdc)) {
        movimenta_estudante(tabuleiro, &cdc, infos);
    }

    
    // Use the 'tabuleiro' variable to avoid unused variable warning
    // For example, you can print or process it
    
    printf("------------------//------------------\n");
    Imprimir_Labirinto(tabuleiro, linhas, colunas);
    Destrutor_Labirinto(tabuleiro, linhas);
    fclose(arquivo);
    return 0;
}*/


// main final
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("%d\n", argc);
        printf("Digitar somente o caminho e o nome do arquivo de entrada\n");
        return 1;
    }
    printf("Arquivo de entrada: %s\n", argv[1]);

    
    estudante cdc;
    cave_infos infos;
    char buffer[128];
    
    strcpy(buffer, argv[1]);
    FILE* arquivo = fopen(buffer,"r");
    int linhas = 0, colunas = 0, pts_vida = 0;
    get_infos(arquivo, &linhas, &colunas, &pts_vida);
    infos.ordem[0] = linhas - 1;
    infos.ordem[1] = colunas - 1;
    


    labirinto tabuleiro = Processar_Arquivo(arquivo,linhas,colunas, &cdc, &infos);
    Criar_Estudante(pts_vida, &cdc);
    if (problema_valido(infos, cdc)) {
        movimenta_estudante(tabuleiro, &cdc, infos);
    }

    

    printf("------------------//------------------\n");
    Imprimir_Labirinto(tabuleiro, linhas, colunas);
    Destrutor_Labirinto(tabuleiro, linhas);
    fclose(arquivo);
    return 0;
}
