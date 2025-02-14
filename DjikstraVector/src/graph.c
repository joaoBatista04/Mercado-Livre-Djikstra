#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/utils.h"
#include "../include/graphVector.h"
struct graphVector
{
    float **weights;
    int nodes_amount;
};

GraphVector *graph_vector_create(int nodes_amount)
{
    GraphVector *graphVector = (GraphVector *)malloc(sizeof(GraphVector));

    graphVector->weights = (float **)malloc((nodes_amount + 1) * sizeof(float *));

    for (int i = 0; i < nodes_amount + 1; i++)
    {
        graphVector->weights[i] = (float *)malloc((nodes_amount + 1) * sizeof(float));
    }

    graphVector->nodes_amount = nodes_amount + 1;

    return graphVector;
}

void graph_vector_add_edges(GraphVector *graph_vector, char *line, int node_id)
{
    char *item = strtok(line, ",\n\t");
    float dist;
    char *aux;

    item = strtok(NULL, ",\n\t");
    for (int i = 0; i < graph_vector->nodes_amount - 1; i++)
    {
        dist = strtof(item, &aux);

        if (i < node_id)
        {
            graph_vector->weights[node_id][i] = dist;
        }

        else if (i == node_id)
        {
            graph_vector->weights[node_id][i] = 0.0;
            graph_vector->weights[node_id][i + 1] = dist;
        }

        else
        {
            graph_vector->weights[node_id][i + 1] = dist;
        }
        item = strtok(NULL, ",\n\t");
    }
}

int graph_vector_get_nodes_amount(GraphVector *graph_vector)
{
    return graph_vector->nodes_amount;
}

float graph_vector_get_distance(GraphVector *graph_vector, int i, int j)
{
    return graph_vector->weights[i][j];
}

// RETIRAR FUNCAO (APENAS DEBUG) =========================================
void printGraph(GraphVector *graph_vector)
{
    for (int i = 0; i < graph_vector->nodes_amount; i++)
    {
        printf("NODE_%d: ", i);
        for (int j = 0; j < graph_vector->nodes_amount; j++)
        {
            printf("node_%d (%f) ", j, graph_vector->weights[i][j]);
        }
        printf("\n");
    }
}

void graph_vector_destroy(GraphVector *graph_vector)
{
    for (int i = 0; i < graph_vector->nodes_amount; i++)
    {
        free(graph_vector->weights[i]);
    }

    free(graph_vector->weights);

    free(graph_vector);
}