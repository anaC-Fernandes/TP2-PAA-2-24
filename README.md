
# Trabalho Prático 2 - Projeto e Análise de Algoritmos

Este repositório contém o código e a documentação do **Trabalho Prático 2** da disciplina de **Projeto e Análise de Algoritmos** da UFV – Campus Florestal.

## Descrição

O objetivo é implementar um algoritmo de **programação dinâmica** em C para encontrar o melhor caminho que maximize os Pontos de Vida (PV) em uma caverna, partindo de uma posição inicial e chegando a uma saída específica. O programa utiliza um arquivo de entrada para definir a configuração da caverna e suas características, como monstros e poções.

## Funcionalidades

1. **Carregar Arquivo**: Leitura dos dados da caverna a partir de um arquivo.
2. **Processar Caminho**:
   - Determinar o melhor caminho entre a posição inicial e a saída.
   - Garantir que o estudante mantenha Pontos de Vida positivos durante todo o trajeto.
   - Detectar quando não é possível escapar com vida.
3. **Salvar Resultado**:
   - Armazenar o trajeto no arquivo `resultado.txt` ou indicar que a saída é impossível.
4. **Modo Otimização** (Opcional):
   - Heurísticas para acelerar a execução.
   - Geração de arquivos de entrada e análise de complexidade.

## Como Usar

### Requisitos
- Compilador GCC.

### Passos
1. Clone o repositório:
   ```bash
   git clone https://github.com/seu_usuario/TP-PAA-2-24.git
   ```
2. Compile o programa:
   ```bash
   make
   ```
3. Execute o programa informando o caminho do arquivo de entrada:
   ```bash
   ./programa entrada.txt
   ```

### Formato do Arquivo de Entrada

- Primeira linha: `<linhas> <colunas> <pontos_de_vida_iniciais>`
- Linhas seguintes: Configuração da caverna, com:
  - **Número positivo**: Poção que adiciona Pontos de Vida.
  - **Número negativo**: Monstro que reduz Pontos de Vida.
  - `I`: Posição inicial.
  - `F`: Posição de saída.

Exemplo:
```
4 5 40
-20 0 -20 0 0
F -10 -10 -10 -10
-20 0 0 0 +20
0 0 -10 0 I
```

### Formato do Arquivo de Saída

- Cada linha contém as coordenadas da posição no formato `<x> <y>`.
- Caso não seja possível escapar, o arquivo conterá apenas:
  ```
  impossível
  ```

Exemplo de saída:
```
4 4
3 4
3 3
3 2
3 1
2 1
2 0
```

## Funcionalidades Extras (Opcional)

1. **Heurísticas**: Uso de algoritmos para otimizar a busca do melhor caminho.
2. **Movimentação Completa**: Alteração do algoritmo para permitir movimentação em todas as direções (norte, sul, leste e oeste).
3. **Geração de Arquivos de Entrada**: Criação automatizada de configurações de caverna.
4. **Análise de Complexidade**: Geração de gráficos comparativos de tempo de execução.

## Autores

- Ana Carolina Fernandes  
- Gabriel Benez Duarte  
- Lucas Fonseca  
- Luiz Felipe Coutinho  
