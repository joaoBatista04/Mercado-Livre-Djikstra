#include <stdio.h>
#include <stdlib.h>
#include "../include/utils.h"

int main(int argc, char *argv[])
{
    char *vsrc;

    Graph *graph = read_graph_informations(&vsrc, argv[1]);

    float *dist = djikstra(graph, 0);

    free(vsrc);
    graph_destroy(graph);

    return 0;
}