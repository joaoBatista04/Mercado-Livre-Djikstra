#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/node.h"
struct node
{
    int id;       // Node id
    float weight; // Distance to next node (connection)
    Node *next;   // Pointer to next node
};

/**
 * @brief Allocate memory and initialize params of a node
 *
 * @param int id
 * @param double weight
 * @return Node*
 */
Node *node_create(int id, float weight)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->id = id;
    node->weight = weight;
    node->next = NULL;

    return node;
}

/**
 * @brief Setter to node's weight
 *
 * @param Node* node
 * @param float weight
 */
void node_set_weight(Node *node, float weight)
{
    node->weight = weight;
}

/**
 * @brief Getter of node's id
 *
 * @param Node* src
 * @return int
 */
int node_get_id(Node *src)
{
    return src->id;
}

/**
 * @brief Getter of node's next node pointer
 *
 * @param Node* src
 * @return Node*
 */
Node *node_get_next(Node *src)
{
    return src->next;
}

/**
 * @brief Getter of node's weight (connection)
 *
 * @param Node* src
 * @return float
 */
float node_get_weight(Node *src)
{
    return src->weight;
}

/**
 * @brief Destroy node by deallocating memory
 *
 * @param Node* node
 */
void node_destroy(Node *node)
{
    free(node);
}

/**
 * @brief Deallocating and destroying all nodes in a vector
 *
 * @param Nodes** vector
 * @param int nodes_amount
 */
void node_vector_destroy(Node **vector, int nodes_amount)
{
    // Runs through all nodes in the vector
    for (int i = 0; i <= nodes_amount; i++)
    {
        Node *node = vector[i];

        // While node has a pointer to the next, free the current and update with the next
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

    // Freeing the vector
    free(vector);
}

/**
 * @brief Creating an edge/connection between two nodes and assigning a weight to this connection. Representation of connections are made according to an adjacency list. The reference used to build this method can be found at https://www.programiz.com/dsa/graph-adjacency-list. Just the first part of assigning in adjacency list was necessary in this program, which helped save memory and time.
 *
 * @param vector
 * @param src
 * @param dest
 * @param value
 */
void node_create_edge(Node **vector, int src, int dest, float value)
{
    // Create a new node and a new connection
    Node *new_node = node_create(dest, value);

    // Assign the current node at vector[src] to pointer to next node (it will build the adjacency list like a linked list)
    new_node->next = vector[src];

    // Update the position [src] at the vector with the new node created (The adjacency list represents connection from the last to the first)
    vector[src] = new_node;
}

/**
 * @brief Verify if first node has a weight greater than second's weight
 *
 * @param Node* node1
 * @param Node* node2
 * @return bool true
 * @return bool false
 */
bool node_more(Node *node1, Node *node2)
{
    bool more = node1->weight > node2->weight;
    return more;
}