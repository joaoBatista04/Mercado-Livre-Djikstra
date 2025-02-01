#include <stdio.h>
#include <stdlib.h>
#include "../include/printer.h"

struct printer
{
    int dest;
    float dist;
};

Printer *printer_init(int dest, float dist)
{
    Printer *p = (Printer *)malloc(sizeof(Printer));

    p->dest = dest;
    p->dist = dist;

    return p;
}

Printer **printer_vector_create(int src, float *dist, int nodeAmount)
{
    Printer **p_vector = (Printer **)calloc(nodeAmount + 1, sizeof(Printer *));

    for (int i = 0; i < nodeAmount; i++)
    {
        Printer *p = printer_init(i, dist[i]);

        p_vector[i] = p;
    }
    return p_vector;
}

int printer_compare(const void *a, const void *b)
{
    const Printer *p1 = *(const Printer **)a;
    const Printer *p2 = *(const Printer **)b;

    if (p1->dist < p2->dist)
    {
        return -1;
    }
    if (p1->dist > p2->dist)
    {
        return 1;
    }
    return 0;
}

void printer_print_path(Printer **p_vector, int src, int nodeAmount, int *path)
{
    for (int i = 0; i <= nodeAmount; i++)
    {
        int current = p_vector[i]->dest;

        if (current == src)
        {
            printf("SHORTEST PATH TO node_%d: node_%d <- node_%d (Distance: 0.00)\n", current, current, current);
        }

        else
        {
            printf("SHORTEST PATH TO node_%d: node_%d", current, current);

            while (path[current] != -1)
            {
                current = path[current];
                printf(" <- node_%d", current);
            }

            printf(" (Distance: %.2f)\n", p_vector[i]->dist);
        }
    }
}

void printer_free(Printer **printer, int nodeAmount)
{
    for (int i = 0; i <= nodeAmount; i++)
    {
        free(printer[i]);
    }

    free(printer);
}