#include "Movimento.h"

bool cima_valido(int proximaLinha, cave_infos infos) {
    //Verificar se a linha do próximo movimento está dentro do limite da matriz
    if(proximaLinha > infos.ordem[0] )return false;
    if(proximaLinha < 0 ) return false;
    // Verificar se o movimento pode ultrapassar a saída
    if(proximaLinha < infos.linhaFim) return false;
    return true;
}

bool esq_valido(int proximaColuna, cave_infos infos) {
    //Verificar se a coluna do próximo movimento está dentro do limite da matriz
    if(proximaColuna > infos.ordem[1]) return false;
    if(proximaColuna < 0) return false;
    // Verificar se o movimento pode ultrapassar a saída
    if(proximaColuna < infos.coluna_fim) return false;
    return true;
}

void NextisEndPoint(labirinto cave, estudante *cdc, cave_infos infos, bool isDead) {
    if(isDead) return;
    bool cima = cima_valido(cdc->linha - 1, infos);
    bool esq = esq_valido(cdc->coluna - 1, infos);
    if(cima == true) {
        if(cave[cdc->linha - 1][cdc->coluna].isEnd == true) {
            cdc->isAtEndPoint = true;
            cdc->linha --;
            cdc->isAtEndPoint = true;
            return;

        }
    }
    if(esq == true) {
        if(cave[cdc->linha][cdc->coluna - 1].isEnd == true) {
            cdc->isAtEndPoint = true;
            cdc->coluna --;
            cdc->isAtEndPoint = true;
        }
    }
}
void escritaArquivo(estudante cdc, bool isDead) {
    FILE *arquivo;
    if (isDead == false) {
         arquivo = fopen("resultado.txt", "a");
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo\n");
            return;
        }
        fprintf(arquivo, "%d %d\n", cdc.linha, cdc.coluna);
    } else {
         arquivo = fopen("resultado.txt", "w");
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo\n");
            return;
        }
        fprintf(arquivo, "impossível\n");
    }

    fclose(arquivo);
}

void primeiraEscrita(estudante cdc) {
    FILE *arquivo = fopen("resultado.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }
    fprintf(arquivo, "%d %d\n", cdc.linha, cdc.coluna);
    fclose(arquivo);
}

int calcular_adj(caverna *cv, labirinto cave, int linhaAtualCelula, int colunaAtualCelula, cave_infos infos, estudante *cdc) { // a matriz completa está sendo passada em

    if(cv->isStudent == true || cdc->isAtEndPoint == true ) {
        return 0;
    }

    if(cv->wasCalculated == true) { // Verificar se o peso do movimento para a celula já foi calculado
        return cv->peso;
    }

    int valorBaixo = 0, valorDir = 0;
    bool dir = esq_valido(colunaAtualCelula + 1, infos);
    bool baixo = cima_valido(linhaAtualCelula + 1, infos);
    if(dir == true) {
        valorDir = calcular_adj(&cave[linhaAtualCelula][colunaAtualCelula + 1], cave, linhaAtualCelula, colunaAtualCelula + 1, infos, cdc);
    }
    if(baixo == true) {
        valorBaixo = calcular_adj(&cave[linhaAtualCelula + 1][colunaAtualCelula], cave, linhaAtualCelula + 1, colunaAtualCelula, infos, cdc);
    }
    if(dir == false && baixo == true) {
        cv->wasCalculated = true;
        cv->peso += valorBaixo + cv->action;
        return cv->peso;
    }
    if(dir == true && baixo == false) {
        cv->wasCalculated = true;
        cv->peso = valorDir + cv->action;
        return cv->peso;
    }
    if(dir == false && baixo == false) {
        cv->wasCalculated = true;
        cv->peso = cv->action;
        return cv->peso;
    }
    if(valorDir >= valorBaixo) { // se o valor da direita for maior ou igual ao de baixo
        cv->wasCalculated = true;
        cv->peso = valorDir + cv->action;
        return cv->peso;
    }
    if(valorBaixo > valorDir) {
        cv->wasCalculated = true;
        cv->peso += valorBaixo + cv->action;
        return cv->peso;
    }
    return 0;
}



void movimenta_estudante(const labirinto cave, estudante *cdc, cave_infos infos) { //passar a ordem da matriz
    bool esq_permitida,cim_permitida;
    bool isDead = false;
    primeiraEscrita(*cdc);
    while(cdc->isAtEndPoint != true) {
        // testar aqui primeiro se a linha e a coluna são iguais a linha e coluna final

        esq_permitida = esq_valido(cdc->coluna - 1, infos);
        cim_permitida = cima_valido(cdc->linha - 1, infos);

        if(esq_permitida == true && cim_permitida == true ) {
            const int esq = calcular_adj(&cave[cdc->linha][cdc->coluna - 1], cave, cdc->linha, cdc->coluna - 1, infos, cdc);
            const int cima = calcular_adj(&cave[cdc->linha - 1][cdc->coluna], cave, cdc->linha - 1, cdc->coluna, infos, cdc);

            if(esq > cima){
                cdc->coluna --; // realiza o movimento para a esquerda
                cdc->vida += cave[cdc->linha][cdc->coluna].action;
            } else {
                cdc->linha --; // realiza o movimento para cima
                cdc->vida += cave[cdc->linha][cdc->coluna].action;
            }
        } else if(esq_permitida == false && cim_permitida == true) {
            cdc->linha --;
            cdc->vida += cave[cdc->linha][cdc->coluna].action;
        } else if(esq_permitida == true && cim_permitida == false) {
            cdc->coluna --;
            cdc->vida += cave[cdc->linha][cdc->coluna].action;
        } else if(cim_permitida == false && esq_permitida == false) {
            isDead = true;
            break;
        }
        escritaArquivo(*cdc, isDead);

        if(cdc->vida <= 0) {
            printf("Estudante morreu\n");
            isDead = true;
            break;
        }
        NextisEndPoint(cave, cdc, infos, isDead);
    }

    if(cdc->isAtEndPoint == true) {
        escritaArquivo(*cdc, isDead);
    } else {
        escritaArquivo(*cdc, isDead);
    }
}
bool problema_valido(cave_infos infos, estudante cdc) {
    if (infos.coluna_fim > cdc.coluna && infos.linhaFim > cdc.linha) {
        escritaArquivo(cdc, true);
        return false;
    }else {
        return true;
    }
}