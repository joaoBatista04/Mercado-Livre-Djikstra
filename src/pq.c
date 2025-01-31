#include <stdio.h>
#include <stdlib.h>
#include "../include/pq.h"

struct priority_queue
{
    Node **nodes;
    int *map;
    int size;
};

PQ *pq_init(int max_size)
{
    PQ *pq = (PQ *)malloc(sizeof(PQ));

    // Memory allocation to priorty queue params
    pq->nodes = (Node **)malloc((max_size + 1) * sizeof(Node *));
    pq->map = (int *)calloc((max_size + 1), sizeof(int));
    pq->size = 0;

    return pq;
}

void pq_destroy(PQ *pq)
{
    free(pq->nodes);
    free(pq->map);
    free(pq);
}

void pq_insert(PQ *pq, Node *node)
{
    pq->size++;

    pq->nodes[pq->size] = node;

    pq->map[node_get_id(node)] = pq->size;

    __fix_up(pq, pq->size);
}

Node *pq_delete_min(PQ *pq)
{
    Node *min = pq->nodes[1];

    __swap(pq, 1, pq->size);

    pq->size--;

    __fix_down(pq, pq->size, 1);

    return min;
}
void pq_decrease_key(PQ *pq, int id, float new_weight)
{
    int i = pq->map[id];

    node_set_weight(pq->nodes[i], new_weight);

    __fix_up(pq, i);
}

bool pq_contains(PQ *pq, int id)
{
    for (int i = 0; i < pq->size; i++)
    {
        if (pq->nodes[i] == NULL)
        {
            return false;
        }

        if (node_get_id(pq->nodes[i]) == id)
        {
            return true;
        }
    }

    return false;
}

bool pq_empty(PQ *pq)
{
    return pq->size == 0;
}

void __swap(PQ *pq, int i, int j)
{
    Node *aux = pq->nodes[i];
    pq->nodes[i] = pq->nodes[j];
    pq->nodes[j] = aux;

    // The position of both nodes is changed in the map
    pq->map[node_get_id(pq->nodes[i])] = i;
    pq->map[node_get_id(pq->nodes[j])] = j;
}

void __fix_up(PQ *pq, int k)
{
    while (k > 1 && node_more(pq->nodes[k / 2], pq->nodes[k]))
    {
        __swap(pq, k, k / 2);
        k = k / 2;
    }
}

void __fix_down(PQ *pq, int sz, int k)
{
    while (2 * k <= sz)
    {
        int j = 2 * k;

        if (j < sz && node_more(pq->nodes[j], pq->nodes[j + 1]))
        {
            j++;
        }

        if (!node_more(pq->nodes[k], pq->nodes[j]))
        {
            break;
        }
        __swap(pq, k, j);
        k = j;
    }
}