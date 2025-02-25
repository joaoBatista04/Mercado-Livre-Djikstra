#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/utils.h"
#include "../include/graphVector.h"

struct graphVector
{
    float **weights;  // Matrix of distances of all nodes to all nodes (node amount x node amount)
    int nodes_amount; // Amount of nodes in the vector
};

/**
 * @brief Allocates memory to a graph and initialize its params
 *
 * @param int nodes_amount
 * @return GraphVector*
 */
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

/**
 * @brief Receives a line from a entry file, processes and extracting weights from it and puts the info obtained into the graph
 *
 * @param GraphVector* graph
 * @param char* line
 * @param int node_id
 */
void graph_vector_add_edges(GraphVector *graph_vector, char *line, int node_id)
{
    // Break the line at commas and line breakers (end of line and spaces)
    char *item = strtok(line, ",\n\t");
    float dist;
    char *aux;

    item = strtok(NULL, ",\n\t");

    // Break the line up to the source node index
    for (int i = 0; i < graph_vector->nodes_amount - 1; i++)
    {
        // Transform the distance from char* to float. By doing it, bombs are just ignored, because strtof won't return a valid value
        dist = strtof(item, &aux);

        // If the current index is lower than the source node id, put the distance in the i position in matrix
        if (i < node_id)
        {
            graph_vector->weights[node_id][i] = dist;
        }

        // If the current index is equal to source node id, put 0 to source node (because the distance from a node to itself is zero) and put the true value in the next index in matrix
        else if (i == node_id)
        {
            graph_vector->weights[node_id][i] = 0.0;
            graph_vector->weights[node_id][i + 1] = dist;
        }

        // If the current index is greater than source node id, put the distance in the next index in matrix (due to entry file's format)
        else
        {
            graph_vector->weights[node_id][i + 1] = dist;
        }

        // Get the next info from line
        item = strtok(NULL, ",\n\t");
    }
}

/**
 * @brief Getter to graph's nodes amount
 *
 * @param GraphVector* graph
 * @return int
 */
int graph_vector_get_nodes_amount(GraphVector *graph_vector)
{
    return graph_vector->nodes_amount;
}

/**
 * @brief Getter to the distance between a node i and a node j
 *
 * @param GraphVector* graph_vector
 * @param int i
 * @param int j
 * @return float
 */
float graph_vector_get_distance(GraphVector *graph_vector, int i, int j)
{
    return graph_vector->weights[i][j];
}

/**
 * @brief Destroys and deallocates memory to a graph
 *
 * @param GraphVector* graph
 */
void graph_vector_destroy(GraphVector *graph_vector)
{
    // Destroy all float pointers
    for (int i = 0; i < graph_vector->nodes_amount; i++)
    {
        free(graph_vector->weights[i]);
    }

    // Destroy the vector of pointers
    free(graph_vector->weights);

    // Freeing the graph
    free(graph_vector);
}