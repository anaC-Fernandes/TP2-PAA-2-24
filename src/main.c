#include "Labirinto.c"
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