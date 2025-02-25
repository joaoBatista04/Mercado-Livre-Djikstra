#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/utils.h"
#include "../include/node.h"
#include "../include/graph.h"
struct graph
{
    Node **nodes;     // Vector of nodes
    int nodes_amount; // Amount of nodes in the vector
};

/**
 * @brief Allocates memory to a graph and initialize its params
 *
 * @param int nodes_amount
 * @return Graph*
 */
Graph *graph_create(int nodes_amount)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));

    graph->nodes = (Node **)malloc((nodes_amount + 1) * sizeof(Node *));

    for (int i = 0; i <= nodes_amount; i++)
    {
        graph->nodes[i] = NULL;
    }

    graph->nodes_amount = nodes_amount;

    return graph;
}

/**
 * @brief Receives a line from a entry file, processes and extracting weights from it and puts the info obtained into the graph
 *
 * @param Graph* graph
 * @param char* line
 * @param int node_id
 */
void graph_add_edges(Graph *graph, char *line, int node_id)
{
    // Break the line at commas and line breakers (end of line and spaces)
    char *item = strtok(line, ",\n\t");
    float dist;
    char *aux;

    item = strtok(NULL, ",\n\t");

    // Break the line up to the source node index
    for (int i = 0; i < node_id; i++)
    {
        // Transform the distance from char* to float. By doing it, bombs are just ignored, because strtof won't return a valid value
        dist = strtof(item, &aux);

        // If the distance is higher than zero, create a new connection in the graph (The adjacency list and Djikstra don't work well with zeros in the graph, so they are just ignored)
        if (i != node_id && dist > 0)
        {
            node_create_edge(graph->nodes, node_id, i, dist);
        }

        // Get the next info from line
        item = strtok(NULL, ",\n\t");
    }

    // Repeat the process, but the index in the graph will be increment by one, to disregard the source node index
    int current_node = node_id + 1;
    while (item)
    {
        dist = strtof(item, &aux);
        if (item != NULL && dist > 0)
        {
            node_create_edge(graph->nodes, node_id, current_node, dist);
        }

        item = strtok(NULL, ",\n\t");
        current_node++;
    }
}

/**
 * @brief Getter to graph's nodes amount
 *
 * @param Graph* graph
 * @return int
 */
int graph_get_nodes_amount(Graph *graph)
{
    return graph->nodes_amount;
}

/**
 * @brief Getter that return a pointer to the node located in the index specified
 *
 * @param Graph* graph
 * @param int index
 * @return Node*
 */
Node *graph_get_node(Graph *graph, int index)
{
    return graph->nodes[index];
}

/**
 * @brief Destroys and deallocates memory to a graph
 *
 * @param Graph* graph
 */
void graph_destroy(Graph *graph)
{
    // Freeing the vector of nodes
    node_vector_destroy(graph->nodes, graph->nodes_amount);

    // Freeing the graph
    free(graph);
}