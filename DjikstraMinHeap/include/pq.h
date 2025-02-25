#ifndef PQ_H
#define PQ_H

#include <stdbool.h>
#include "./node.h"

typedef struct priority_queue PQ;

//======================= MEMORY FUNCTIONS =======================
PQ *pq_init(int max_size);
void pq_destroy(PQ *pq);

//======================= SETTERS =======================
void pq_insert(PQ *pq, Node *node);

//======================= GETTERS =======================
bool pq_contains(PQ *pq, int id);
bool pq_empty(PQ *pq);

//======================= PRIORITY QUEUE SPECIAL FUNCTIONS =======================
void pq_decrease_key(PQ *pq, int id, float new_weight);
Node *pq_delete_min(PQ *pq);

//======================= PRIORITY QUEUE AUXILIARY FUNCTIONS =======================
void __swap(PQ *pq, int i, int j);
void __fix_up(PQ *pq, int k);
void __fix_down(PQ *pq, int sz, int k);

#endif