#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/utils.h"

int main(int argc, char *argv[])
{
    char *vsrc;

    // Creates the graph by read info from an entry file and gets the source node
    GraphVector *graph_vector = read_graph_informations(&vsrc, argv[1]);

    // Inialize the vector of distances and paths, which will be used to calculate min distances with djikstra
    int nodeAmount = graph_vector_get_nodes_amount(graph_vector);
    float *dist = (float *)malloc((nodeAmount + 1) * sizeof(float));
    int *path = (int *)malloc((nodeAmount + 1) * sizeof(int));

    // Gets the source node id from the string obtained before
    int src;
    sscanf(vsrc, "node_%d", &src);

    // Calculates min distances from each node to the source node (and saves the path)
    djikstra(graph_vector, src, dist, path);

    // Orders the distances and print they with the paths
    print_shortest_path(path, dist, src, nodeAmount, argv[2]);

    // Prevents memory leaks
    free(vsrc);
    free(dist);
    free(path);
    graph_vector_destroy(graph_vector);

    return 0;
}