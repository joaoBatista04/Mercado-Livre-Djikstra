#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "../include/printer.h"
#include "../include/utils.h"

Graph *read_graph_informations(char **vsrc, char *path)
{
    FILE *fp = fopen(path, "r");

    if (fp == NULL)
    {
        perror("SOURCE FILE NOT FOUND!\n");
        exit(1);
    }

    char *current_line = NULL;
    size_t size = 0;

    getline(&current_line, &size, fp);
    *vsrc = strdup(current_line);

    getline(&current_line, &size, fp);
    int nodes_amount = get_nodes_amount(current_line);

    Graph *graph = graph_create(nodes_amount);
    int i = 0;

    graph_add_edges(graph, current_line, i);
    i++;

    while (getline(&current_line, &size, fp) != -1)
    {
        graph_add_edges(graph, current_line, i);
        i++;
    }

    free(current_line);
    fclose(fp);

    return graph;
}

int get_nodes_amount(char *current_line)
{
    int nodes_amount = -1;
    char *aux = strdup(current_line);
    char *item = strtok(aux, ",");

    while (item)
    {
        nodes_amount++;

        item = strtok(NULL, ",");
    }

    free(aux);

    return nodes_amount;
}

int get_number_id(char *name)
{
    int number;
    sscanf(name, "node_%d", &number);
    return number;
}

void djikstra(Graph *graph, int src, float *dist, int *path)
{
    int nodeAmount = graph_get_nodes_amount(graph);
    int *visited = calloc(nodeAmount + 1, sizeof(int));

    for (int i = 0; i <= nodeAmount; i++)
    {
        // All the distances between a origin node and a destination node are initialized with infinity. This value is used in comparisons because it is big and any smaller distance is considered later in the algorithm
        dist[i] = INFINITY;
        path[i] = -1;
    }

    // The distance of the node to itself is 0
    dist[src] = 0.0;

    for (int i = 0; i < nodeAmount - 1; i++)
    {
        int u = __get_min_distance(dist, visited, nodeAmount);

        visited[u] = 1;

        for (int i = 0; i < nodeAmount; i++)
        {
            float dist_v = graph_get_distance(graph, u, i);
            if (visited[i] == 0 && dist_v && dist[u] != INFINITY && dist[u] + dist_v < dist[i])
            {
                dist[i] = dist[u] + dist_v;
                path[i] = u;
            }
        }
    }

    free(visited);
}

int __get_min_distance(float *dist, int *visited, int node_amount)
{
    float min = INFINITY;
    int min_index;

    for (int i = 0; i < node_amount; i++)
    {
        if (visited[i] == 0 && dist[i] <= min)
        {
            min = dist[i];
            min_index = i;
        }
    }

    return min_index;
}

void print_shortest_path(int *path, float *dist, int src, int nodeAmount, char *file_path)
{
    Printer **p_vector = printer_vector_create(src, dist, nodeAmount);

    qsort(p_vector, nodeAmount, sizeof(Printer *), printer_compare);

    printer_print_path(p_vector, src, nodeAmount, path, file_path);

    printer_free(p_vector, nodeAmount);
}