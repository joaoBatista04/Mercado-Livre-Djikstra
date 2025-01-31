#ifndef PQ_H
#define PQ_H

#include <stdbool.h>
#include "./node.h"

typedef struct priority_queue PQ;

PQ *pq_init(int max_size);
void pq_destroy(PQ *pq);
void pq_insert(PQ *pq, Node *node);
Node *pq_delete_min(PQ *pq);
void pq_decrease_key(PQ *pq, int id, float new_weight);
bool pq_contains(PQ *pq, int id);

bool pq_empty(PQ *pq);
void __swap(PQ *pq, int i, int j);
void __fix_up(PQ *pq, int k);
void __fix_down(PQ *pq, int sz, int k);

#endif