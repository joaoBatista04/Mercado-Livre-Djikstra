#include <stdio.h>
#include <stdlib.h>
#include "../include/printer.h"
struct printer
{
    int dest;   // Current node
    float dist; // Dist from source
};

/**
 * @brief Allocated and initialize memory to a printer
 *
 * @param int dest
 * @param float dist
 * @return Printer*
 */
Printer *printer_init(int dest, float dist)
{
    Printer *p = (Printer *)malloc(sizeof(Printer));

    p->dest = dest;
    p->dist = dist;

    return p;
}

/**
 * @brief Create a vector the size of the number of nodes in graph
 *
 * @param int src
 * @param float* dist
 * @param int nodeAmount
 * @return Printer**
 */
Printer **printer_vector_create(int src, float *dist, int nodeAmount)
{
    // Allocate memory to the vector
    Printer **p_vector = (Printer **)calloc(nodeAmount + 1, sizeof(Printer *));

    // For each element in vector, initialize it with the distance of a node to source
    for (int i = 0; i < nodeAmount; i++)
    {
        Printer *p = printer_init(i, dist[i]);

        p_vector[i] = p;
    }
    return p_vector;
}

/**
 * @brief Auxiliary function to compare two printers. Used in qsort function call
 *
 * @param const void* a
 * @param const void* b
 * @return int
 */
int printer_compare(const void *a, const void *b)
{
    const Printer *p1 = *(const Printer **)a;
    const Printer *p2 = *(const Printer **)b;

    // If node 2 has a distance higher than node 1, return -1
    if (p1->dist < p2->dist)
    {
        return -1;
    }

    // If node 1 has a distance higher than node 2, return 1
    if (p1->dist > p2->dist)
    {
        return 1;
    }

    // If the distances are equal, return 0
    return 0;
}

/**
 * @brief Print the path from all nodes to source using a ordered vector of printers
 *
 * @param Printer** p_vector
 * @param int src
 * @param int nodeAmount
 * @param int* path
 * @param char* file_path
 */
void printer_print_path(Printer **p_vector, int src, int nodeAmount, int *path, char *file_path)
{
    // Open a file to write the results
    FILE *fp = fopen(file_path, "w");
    if (!fp)
    {
        perror("THE SYSTEM COULDN'T GENERATE THE EXIT FILE\n");
        exit(1);
    }

    // For each node, print its distance to a source using a Printer (ordered)
    for (int i = 0; i <= nodeAmount; i++)
    {
        int current = p_vector[i]->dest;

        // If the node is about to print the dist for itself, print 0 as distance
        if (current == src)
        {
            fprintf(fp, "SHORTEST PATH TO node_%d: node_%d <- node_%d (Distance: 0.00)\n", current, current, current);
        }

        else
        {
            // Print the info of distances from a node to source
            fprintf(fp, "SHORTEST PATH TO node_%d: node_%d", current, current);

            // Repeat until the path doesn't end
            while (path[current] != -1)
            {
                current = path[current];
                fprintf(fp, " <- node_%d", current);
            }

            // Finally, print the distance between source and a node
            fprintf(fp, " (Distance: %.2f)\n", p_vector[i]->dist);
        }
    }

    // Close the exit file
    fclose(fp);
}

/**
 * @brief Free memory allocated to a vector of printers
 *
 * @param Printer** printer
 * @param int nodeAmount
 */
void printer_free(Printer **printer, int nodeAmount)
{
    for (int i = 0; i <= nodeAmount; i++)
    {
        free(printer[i]);
    }

    free(printer);
}