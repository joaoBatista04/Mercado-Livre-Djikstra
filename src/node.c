#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/node.h"

struct node
{
    int id;
    float weight;
    Node *next;
};

Node *node_create(int id, double weight)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->id = id;
    node->weight = weight;
    node->next = NULL;

    return node;
}

void node_set_weight(Node *node, float weight)
{
    node->weight = weight;
}

/*RETIRAR (APENAS DEBUG)*/
int node_get_id(Node *src)
{
    return src->id;
}

/*RETIRAR (APENAS DEBUG)*/
Node *node_get_next(Node *src)
{
    return src->next;
}

/*RETIRAR (APENAS DEBUG)*/
float node_get_weight(Node *src)
{
    return src->weight;
}

void node_destroy(Node *node)
{
    free(node);
}

void node_vector_destroy(Node **vector, int nodes_amount)
{
    for (int i = 0; i <= nodes_amount; i++)
    {
        Node *node = vector[i];

        while (node)
        {
            Node *aux = node;
            node = node->next;

            if (aux)
            {
                free(aux);
            }
        }
    }

    free(vector);
}

void node_create_edge(Node **vector, int src, int dest, char *value)
{
    char *aux;
    Node *new_node = node_create(dest, strtof(value, &aux));
    new_node->next = vector[src];
    vector[src] = new_node;
}

bool node_more(Node *node1, Node *node2)
{
    bool more = node1->weight > node2->weight;
    return more;
}

/* RETIRAR, APENAS PARA DEBUG */
void printNode(Node *node)
{
    if (node)
    {
        printf("NODE %d: %f\n", node->id, node->weight);
    }
}