#ifndef NODE_H
#define NODE_H

#include <stdbool.h>

typedef struct node Node;

Node *node_create(int id, double weight);
int node_get_id(Node *src);
void node_set_weight(Node *node, float weight);
Node *node_get_next(Node *src);
float node_get_weight(Node *src);
void node_create_edge(Node **vector, int src, int dest, double value);
void node_destroy(Node *node);
void node_vector_destroy(Node **vector, int nodes_amount);
bool node_more(Node *node1, Node *node2);

Node **node_initialize(int nodeAmount);

void printNode(Node *node);

#endif