FILES = src/node.c src/graph.c src/pq.c src/utils.c src/main.c
EXECUTABLE = trab1
FLAGS = -lm -pedantic -Wall -g
ENTRY_FILE = in/teste_antigo.txt
EXIT_FILE = out_N10000_S50_C300_M10.txt

all: 
	@ gcc -o $(EXECUTABLE) $(FILES) $(FLAGS)

run: 
	@ ./$(EXECUTABLE) $(ENTRY_FILE) $(EXIT_FILE)

clean:
	@ rm -f trab1 out_N10_S3_C3_M3.txt

val:
	@ valgrind --leak-check=full --show-leak-kinds=all ./$(EXECUTABLE) $(ENTRY_FILE) $(EXIT_FILE)