#ifndef NODE_H
#define NODE_H

#include <stdbool.h>

typedef struct node Node;

//======================= MEMORY FUNCTIONS =======================
Node *node_create(int id, float weight);
void node_destroy(Node *node);
void node_vector_destroy(Node **vector, int nodes_amount);

//======================= SETTERS =======================
void node_set_weight(Node *node, float weight);
void node_create_edge(Node **vector, int src, int dest, float value);

//======================= GETTERS =======================
int node_get_id(Node *src);
Node *node_get_next(Node *src);
float node_get_weight(Node *src);
bool node_more(Node *node1, Node *node2);

#endif