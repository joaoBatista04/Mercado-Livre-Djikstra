#include <stdio.h>
#include <stdlib.h>
#include "../include/pq.h"
struct priority_queue
{
    Node **nodes;    // Vector of nodes where the min-heap will be represented
    int *map;        // Map with the position of each node
    int size;        // Priority queue's size
    Node *reference; // A silly reference to a NULL node, just to initialize all the positions of the priority queue (For some reason, initialize the queue with calloc or just NULL instead of this break the code and get a SIGSEGV, C eww *_*)
};

/**
 * @brief This functions allocates memory to the priority queue, based on the nodes amount.
 *
 * @param int max_size (nodes amount)
 * @return PQ* (priority queue)
 */
PQ *pq_init(int max_size)
{
    // Allocate memory to a priority queue and keep a reference into it to initialize
    PQ *pq = (PQ *)malloc(sizeof(PQ));

    // Initialize the reference with a impossible node
    pq->reference = node_create(-1, -0.5);

    // Memory allocation to priorty queue params
    pq->nodes = (Node **)malloc((max_size + 1) * sizeof(Node *));

    // Initialize all the nodes with the reference
    for (int i = 0; i < max_size; i++)
    {
        pq->nodes[i] = pq->reference;
    }

    pq->map = (int *)calloc((max_size + 1), sizeof(int));
    pq->size = 0;

    return pq;
}

/**
 * @brief This function frees up the allocated memory to the priority queue.
 *
 * @param PQ* pq The priority queue to be destroyed.
 */
void pq_destroy(PQ *pq)
{
    free(pq->nodes);
    free(pq->map);
    node_destroy(pq->reference);
    free(pq);
}

/**
 * @brief This functions inserts a new item into the priority queue, updating its parameters.
 *
 * @param PQ* pq The priority queue to be operated.
 * @param Node* node The new node item to be inserted.
 */
void pq_insert(PQ *pq, Node *node)
{
    // Increase the size of the queue
    pq->size++;

    // Put the node in the last position
    pq->nodes[pq->size] = node;

    // Put the node's position into the node's map
    pq->map[node_get_id(node)] = pq->size;

    // Make the fix up to fix the heap after a new item was inserted
    __fix_up(pq, pq->size);
}

/**
 * @brief This function deletes the minimum item (the lowest weight of an edge) from the priority queue, returning it to the user.
 *
 * @param PQ* pq The priority queue to be operated.
 * @return Node* The node that was deleted.
 */
Node *pq_delete_min(PQ *pq)
{
    // Change the first node with the last
    Node *min = pq->nodes[1];

    __swap(pq, 1, pq->size);

    // Decrease priority queue size
    pq->size--;

    // Make the fix down to fix the heap after a item was excluded
    __fix_down(pq, pq->size, 1);

    return min;
}

/**
 * @brief This function updates the value of an edge that is contained in the priority queue.
 *
 * @param PQ* pq The priority queue to be operated.
 * @param int id The ID of the connection's origin node.
 * @param new_weight distance The new value of the weight of the connection.
 */
void pq_decrease_key(PQ *pq, int id, float new_weight)
{
    // Get the position of the node chosen
    int i = pq->map[id];

    // Change the weight of the node
    node_set_weight(pq->nodes[i], new_weight);

    // Make a fix up to fix the heap after change a priority in one of its nodes
    __fix_up(pq, i);
}

/**
 * @brief This function returns true if the connection whose origin is represented by the ID is contained in the priority queue. Otherwise, it returns false.
 *
 * @param Pq* pq The priority queue to be operated.
 * @param int id The index of the node to be consulted.
 * @return true or false.
 */
bool pq_contains(PQ *pq, int id)
{
    // Run into the priority queue and verify if the node is present
    for (int i = 0; i < pq->size; i++)
    {
        // If the node is NULL, return false
        if (pq->nodes[i] == NULL)
        {
            return false;
        }

        // If the node's id corresponds with the id given, return true
        if (node_get_id(pq->nodes[i]) == id)
        {
            return true;
        }
    }

    // The node wasn't found, than return false
    return false;
}

/**
 * @brief This function returns true if the priority queue is empty. Otherwise, it returns false.
 *
 * @param PQ* pq
 * @return true
 * @return false
 */
bool pq_empty(PQ *pq)
{
    return pq->size == 0;
}

/**
 * @brief This function changes the position of two items contained in the priority queue, rearranging the true position of all nodes (to keep the priority queue properties).
 *
 * @param PQ* pq The priority queue to be operated.
 * @param int i The index of the first item to be moved.
 * @param int j The index of the second item to bem moved.
 */
void __swap(PQ *pq, int i, int j)
{
    Node *aux = pq->nodes[i];
    pq->nodes[i] = pq->nodes[j];
    pq->nodes[j] = aux;

    // The position of both nodes is changed in the map
    pq->map[node_get_id(pq->nodes[i])] = i;
    pq->map[node_get_id(pq->nodes[j])] = j;
}

/**
 * @brief This function does the heapify up operation, to rearranging the items positions in the priority queue, keeping the properties of a priority queue based in min-heap.
 *
 * @param PQ* pq The priority queue to be operated.
 * @param int k The index of the item to bem moved.
 */
void __fix_up(PQ *pq, int k)
{
    // Do swap between a node and its parent if k > 1 and if parent is higher than child
    while (k > 1 && node_more(pq->nodes[k / 2], pq->nodes[k]))
    {
        // Swap a child node and its parent
        __swap(pq, k, k / 2);
        k = k / 2;
    }
}

/**
 * @brief This function does the heapify down operation, to rearraging the items positions in the priority queue, keeping the properties of a priority queue based in min-heap.
 *
 * @param PQ* pq The priority queue to be moved.
 * @param int sz The current size of the priority queue.
 * @param int k The index of the item to be moved.
 */
void __fix_down(PQ *pq, int sz, int k)
{
    while (2 * k <= sz)
    {
        // Get the first child index of a node
        int j = 2 * k;

        // If the first child is higher than the second one (j + 1), increment j
        if (j < sz && node_more(pq->nodes[j], pq->nodes[j + 1]))
        {
            j++;
        }

        // If child isn't higher than its parent, break the loop
        if (!node_more(pq->nodes[k], pq->nodes[j]))
        {
            break;
        }

        // If not, change the node with one of its children
        __swap(pq, k, j);

        // Update k with child's position
        k = j;
    }
}