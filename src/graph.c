#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/utils.h"
#include "../include/node.h"
#include "../include/graph.h"

struct graph
{
    Node **nodes;
    int nodes_amount;
};

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

void graph_add_edges(Graph *graph, char *line, int node_id)
{
    char *item = strtok(line, ",\n\t");
    float dist;
    char *aux;

    item = strtok(NULL, ",\n\t");
    for (int i = 0; i < node_id; i++)
    {
        dist = strtof(item, &aux);
        if (i != node_id && dist > 0)
        {
            node_create_edge(graph->nodes, node_id, i, dist);
        }
        item = strtok(NULL, ",\n\t");
    }

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

// RETIRAR ==== DEBUG LEITURA ESTÁTICA
void graph_add_edges_2(Graph *graph, int src, int dest, float weight)
{
    if (weight > 0)
    {
        node_create_edge(graph->nodes, src, dest, weight);
    }
}

int graph_get_nodes_amount(Graph *graph)
{
    return graph->nodes_amount;
}

Node *graph_get_node(Graph *graph, int index)
{
    return graph->nodes[index];
}

// RETIRAR FUNCAO (APENAS DEBUG) =========================================
void printGraph(Graph *graph)
{
    int v;
    for (v = 0; v <= graph->nodes_amount; v++)
    {
        Node *temp = graph->nodes[v];
        printf("\n Vertex node_%d\n: ", v);
        while (temp)
        {
            printf("%d (%f) -> ", node_get_id(temp), node_get_weight(temp));
            temp = node_get_next(temp);
        }
        printf("\n");
    }
}

void graph_destroy(Graph *graph)
{
    node_vector_destroy(graph->nodes, graph->nodes_amount);

    free(graph);
}