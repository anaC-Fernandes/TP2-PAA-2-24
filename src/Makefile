all: compile

compile:
	@echo "Compilando..."
	@gcc Labirinto.h Labirinto.c Movimento.h Movimento.c main.c -o programa
	@echo "Digite ./programa e o caminho do arquivo de entrada para executar o programa."

mapa:
	@echo "Gerando mapa..."
	@gcc GeraLabirinto.c -o GeraLabirinto
	@echo "Digite ./GeraLabirinto para executar o programa."