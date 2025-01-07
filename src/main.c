#include <stdio.h>
#include <stdlib.h>
#include "Labirinto.c"


//main de teste
int main(){
    char buffer[128];
    printf("Digite o caminho do arquivo: ");
    scanf("%s", buffer);
    FILE* arquivo = fopen(buffer,"r");
    int linhas = 0, colunas = 0, pts_vida = 0;
    get_infos(arquivo, &linhas, &colunas, &pts_vida);
    
    labirinto tabuleiro = Processar_Arquivo(arquivo,linhas,colunas);
    // Use the 'tabuleiro' variable to avoid unused variable warning
    // For example, you can print or process it

    printf("------------------//------------------\n");
    Imprimir_Labirinto(tabuleiro, linhas, colunas);
    Destrutor_Labirinto(tabuleiro, linhas);
    fclose(arquivo);
    return 0;
}


// main final
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <caminho-do-arquivo-mapa> <caminho-do-arquivo-resultado>\n", argv[0]);
        return 1;
    }


    FILE* arquivo = fopen(argv[1],"r");
    int linhas = 0, colunas = 0, pts_vida = 0;
    get_infos(arquivo, &linhas, &colunas, &pts_vida);
    
    labirinto tabuleiro = Processar_Arquivo(arquivo,linhas,colunas);
    // Use the 'tabuleiro' variable to avoid unused variable warning
    // For example, you can print or process it

    printf("------------------//------------------\n");
    Imprimir_Labirinto(tabuleiro, linhas, colunas);
    Destrutor_Labirinto(tabuleiro, linhas);
    fclose(arquivo);

    return 0;
}
