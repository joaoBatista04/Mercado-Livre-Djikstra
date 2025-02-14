#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/utils.h"

int main(int argc, char *argv[])
{
    char *vsrc;

    clock_t start = clock();
    GraphVector *graph_vector = read_graph_informations(&vsrc, argv[1]);
    clock_t end = clock();

    int nodeAmount = graph_vector_get_nodes_amount(graph_vector);
    float *dist = (float *)malloc((nodeAmount + 1) * sizeof(float));
    int *path = (int *)malloc((nodeAmount + 1) * sizeof(int));

    int src;
    sscanf(vsrc, "node_%d", &src);

    clock_t start2 = clock();
    djikstra(graph_vector, src, dist, path);
    clock_t end2 = clock();

    float result = ((float)end - (float)start) / CLOCKS_PER_SEC;
    float result2 = ((float)end2 - (float)start2) / CLOCKS_PER_SEC;

    printf("TEMPO DE LEITURA: %f\nDJIKSTRA: %f\n", result, result2);

    print_shortest_path(path, dist, src, nodeAmount, argv[2]);

    free(vsrc);
    free(dist);
    free(path);
    graph_vector_destroy(graph_vector);

    return 0;
}