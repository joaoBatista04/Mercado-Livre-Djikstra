#ifndef GRAPH_H
#define GRAPH_H

#include "./node.h"

typedef struct graph Graph;

//======================= MEMORY FUNCTIONS =======================
Graph *graph_create(int nodes_amount);
void graph_destroy(Graph *graph);

//======================= SETTERS =======================
void graph_add_edges(Graph *graph, char *line, int node_id);

//======================= GETTERS =======================
int graph_get_nodes_amount(Graph *graph);
Node *graph_get_node(Graph *graph, int index);

#endif