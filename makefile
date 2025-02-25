FILESHEAP = DjikstraMinHeap/src/node.c DjikstraMinHeap/src/graph.c DjikstraMinHeap/src/pq.c DjikstraMinHeap/src/printer.c DjikstraMinHeap/src/utils.c DjikstraMinHeap/src/main.c

FILESVECTOR = DjikstraVector/src/graphVector.c DjikstraVector/src/printer.c DjikstraVector/src/utils.c DjikstraVector/src/main.c

EXECUTABLE = trab1
FLAGS = -lm -pedantic -Wall -g
ENTRY_FILE = in/caso_teste_medio_1.txt
EXIT_FILE = saida.txt

vector:
	@ gcc -o $(EXECUTABLE) $(FILESVECTOR) $(FLAGS)

heap:
	@ gcc -o $(EXECUTABLE) $(FILESHEAP) $(FLAGS)

run: 
	@ ./$(EXECUTABLE) $(ENTRY_FILE) $(EXIT_FILE)

diff:
	@ diff saida.txt saida1.txt


clean:
	@ rm -f trab1 *.txt

val:
	@ valgrind --leak-check=full --show-leak-kinds=all ./$(EXECUTABLE) $(ENTRY_FILE) $(EXIT_FILE)