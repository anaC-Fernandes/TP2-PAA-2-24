#include "Movimento.h"

bool Vertical_valido(int proximaLinha, cave_infos infos) {
    //Verificar se a linha do próximo movimento está dentro do limite da matriz
    if(proximaLinha > infos.ordem[0] )return false;
    if(proximaLinha < 0 ) return false;
    // Verificar se o movimento pode ultrapassar a saída
    if(proximaLinha < infos.linhaFim) return false;
    return true;
}

bool Horizontal_valido(int proximaColuna, cave_infos infos) {
    //Verificar se a coluna do próximo movimento está dentro do limite da matriz
    if(proximaColuna > infos.ordem[1]) return false;
    if(proximaColuna < 0) return false;
    // Verificar se o movimento pode ultrapassar a saída
    if(proximaColuna < infos.coluna_fim) return false;
    return true;
}

void NextisEndPoint(labirinto cave, estudante *cdc, cave_infos infos, bool isDead) {
    //Função responsável por verificar se o estudante chegou ao ponto final
    if(isDead) return;
    bool cima = Vertical_valido(cdc->linha - 1, infos);
    bool esq = Horizontal_valido(cdc->coluna - 1, infos);
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
void EscritaArquivo(estudante cdc, bool isDead) { // Função responsável por escrever no arquivo a posição do estudante ou se ele morreu
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

void PrimeiraEscrita(estudante cdc) { //Função responsável por fazer a escrita no arquivo da posicao incial em que o estudante está
    FILE *arquivo = fopen("resultado.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }
    fprintf(arquivo, "%d %d\n", cdc.linha, cdc.coluna);
    fclose(arquivo);
}

int Calcular_adj(caverna *cv, labirinto cave, int linhaAtualCelula, int colunaAtualCelula, cave_infos infos, estudante *cdc) { // a matriz completa está sendo passada em
    //Função responsável por calcular, ou recurperar, recursivamente o valor que será adicionado a vida do estudante caso ele visite a celula
    if(cv->isStudent == true || cdc->isAtEndPoint == true ) {
        return 0;
    }

    if(cv->wasCalculated == true) { // Verificar se o peso do movimento para a celula já foi calculado
        return cv->peso;
    }

    int valorBaixo = 0, valorDir = 0;
    bool dir = Horizontal_valido(colunaAtualCelula + 1, infos);
    bool baixo = Vertical_valido(linhaAtualCelula + 1, infos);
    if(dir == true) {
        valorDir = Calcular_adj(&cave[linhaAtualCelula][colunaAtualCelula + 1], cave, linhaAtualCelula, colunaAtualCelula + 1, infos, cdc);
    }
    if(baixo == true) {
        valorBaixo = Calcular_adj(&cave[linhaAtualCelula + 1][colunaAtualCelula], cave, linhaAtualCelula + 1, colunaAtualCelula, infos, cdc);
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

void Atualiza_posicao(estudante *cdc, int novaLinha, int novaColuna, labirinto cave) {
    cdc->linha = novaLinha;
    cdc->coluna = novaColuna;
    cdc->vida += cave[novaLinha][novaColuna].action;
}


void Movimenta_estudante(const labirinto cave, estudante *cdc, cave_infos infos) {
    bool esq_permitida, cim_permitida;
    bool isDead = false;

    // Escreve a posição inicial no arquivo
    PrimeiraEscrita(*cdc);

    while (!cdc->isAtEndPoint) {
        // Verifica se os movimentos para cima e para a esquerda são permitidos
        esq_permitida = Horizontal_valido(cdc->coluna - 1, infos);
        cim_permitida = Vertical_valido(cdc->linha - 1, infos);

        // Se pelo menos um movimento for permitido
        if (esq_permitida || cim_permitida) {
            int proxLinha = cdc->linha, proxColuna = cdc->coluna;

            // Se ambos os movimentos forem permitidos, escolhe o melhor
            if (esq_permitida && cim_permitida) {
                int pesoEsq = Calcular_adj(&cave[cdc->linha][cdc->coluna - 1], cave, cdc->linha, cdc->coluna - 1, infos, cdc);
                int pesoCima = Calcular_adj(&cave[cdc->linha - 1][cdc->coluna], cave, cdc->linha - 1, cdc->coluna, infos, cdc);

                if (pesoEsq > pesoCima) {
                    proxColuna--; // Move para a esquerda
                } else {
                    proxLinha--; // Move para cima
                }
            } else if (esq_permitida) {
                proxColuna--; // Move apenas para a esquerda
            } else {
                proxLinha--; // Move apenas para cima
            }

            // Atualiza a posição do estudante e os pontos de vida
            Atualiza_posicao(cdc, proxLinha, proxColuna, cave);
            EscritaArquivo(*cdc, isDead);

            // Verifica se o estudante morreu
            if (cdc->vida <= 0) {
                printf("Estudante morreu\n");
                isDead = true;
                break;
            }

            // Verifica se o estudante chegou ao ponto final
            NextisEndPoint(cave, cdc, infos, isDead);

        } else {
            // Nenhum movimento é permitido, estudante não pode continuar
            isDead = true;
            break;
        }
    }

    // Escrita final dependendo do estado do estudante
    EscritaArquivo(*cdc, isDead);
}

//função responsável por verificar se o estudante pode chegar ao ponto final usando as restricoes de movimento do problema
bool Problema_valido(cave_infos infos, estudante cdc) {
    if (infos.coluna_fim > cdc.coluna && infos.linhaFim > cdc.linha) {
        EscritaArquivo(cdc, true);
        return false;
    }else {
        return true;
    }
}