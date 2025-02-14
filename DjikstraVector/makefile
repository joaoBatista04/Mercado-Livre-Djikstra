FILES = src/graph.c src/printer.c src/utils.c src/main.c
EXECUTABLE = trab1
FLAGS = -lm -pedantic -Wall -g
ENTRY_FILE = in/caso_teste_pequeno_1.txt
EXIT_FILE = saida.txt

all: 
	@ gcc -o $(EXECUTABLE) $(FILES) $(FLAGS)

run: 
	@ ./$(EXECUTABLE) $(ENTRY_FILE) $(EXIT_FILE)

clean:
	@ rm -f trab1 saida.txt

val:
	@ valgrind --leak-check=full --show-leak-kinds=all ./$(EXECUTABLE) $(ENTRY_FILE) $(EXIT_FILE)