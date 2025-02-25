#ifndef GRAPH_VECTOR_H
#define GRAPH_VECTOR_H

typedef struct graphVector GraphVector;

//======================= MEMORY FUNCTIONS =======================
GraphVector *graph_vector_create(int nodes_amount);
void graph_vector_destroy(GraphVector *graph);

//======================= SETTERS =======================
void graph_vector_add_edges(GraphVector *graph, char *line, int node_id);

//======================= GETTERS =======================
int graph_vector_get_nodes_amount(GraphVector *graph);
float graph_vector_get_distance(GraphVector *graph, int i, int j);

#endif