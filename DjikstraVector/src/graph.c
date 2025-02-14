#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/utils.h"
#include "../include/graph.h"

struct graph
{
    float **weights;
    int nodes_amount;
};

Graph *graph_create(int nodes_amount)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));

    graph->weights = (float **)malloc((nodes_amount + 1) * sizeof(float *));

    for (int i = 0; i < nodes_amount + 1; i++)
    {
        graph->weights[i] = (float *)malloc((nodes_amount + 1) * sizeof(float));
    }

    graph->nodes_amount = nodes_amount + 1;

    return graph;
}

void graph_add_edges(Graph *graph, char *line, int node_id)
{
    char *item = strtok(line, ",\n\t");
    float dist;
    char *aux;

    item = strtok(NULL, ",\n\t");
    for (int i = 0; i < graph_get_nodes_amount(graph) - 1; i++)
    {
        dist = strtof(item, &aux);

        if (i < node_id)
        {
            graph->weights[node_id][i] = dist;
        }

        else if (i == node_id)
        {
            graph->weights[node_id][i] = 0.0;
            graph->weights[node_id][i + 1] = dist;
        }

        else
        {
            graph->weights[node_id][i + 1] = dist;
        }
        item = strtok(NULL, ",\n\t");
    }
}

int graph_get_nodes_amount(Graph *graph)
{
    return graph->nodes_amount;
}

float graph_get_distance(Graph *graph, int i, int j)
{
    return graph->weights[i][j];
}

// RETIRAR FUNCAO (APENAS DEBUG) =========================================
void printGraph(Graph *graph)
{
    for (int i = 0; i < graph->nodes_amount; i++)
    {
        printf("NODE_%d: ", i);
        for (int j = 0; j < graph->nodes_amount; j++)
        {
            printf("node_%d (%f) ", j, graph->weights[i][j]);
        }
        printf("\n");
    }
}

void graph_destroy(Graph *graph)
{
    for (int i = 0; i < graph->nodes_amount; i++)
    {
        free(graph->weights[i]);
    }

    free(graph->weights);

    free(graph);
}