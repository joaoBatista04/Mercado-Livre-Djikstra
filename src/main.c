#include <stdio.h>
#include <stdlib.h>
#include "../include/utils.h"

int main(int argc, char *argv[])
{
    char *vsrc;

    Graph *graph = read_graph_informations(&vsrc, argv[1]);

    int nodeAmount = graph_get_nodes_amount(graph);
    float *dist = (float *)malloc(nodeAmount * sizeof(float));
    int *path = (int *)malloc(nodeAmount * sizeof(int));

    int src;
    sscanf(vsrc, "node_%d", &src);

    djikstra(graph, src, dist, path);

    print_shortest_path(path, dist, src, nodeAmount);

    free(vsrc);
    free(dist);
    free(path);
    graph_destroy(graph);

    return 0;
}