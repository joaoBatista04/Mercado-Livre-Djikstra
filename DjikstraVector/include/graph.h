#ifndef GRAPH_H
#define GRAPH_H

typedef struct graph Graph;

Graph *graph_create(int nodes_amount);
void graph_add_edges(Graph *graph, char *line, int node_id);

int graph_get_nodes_amount(Graph *graph);
float graph_get_distance(Graph *graph, int i, int j);
void printGraph(Graph *graph);
void graph_destroy(Graph *graph);

#endif