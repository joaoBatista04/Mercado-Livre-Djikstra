#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "../include/printer.h"
#include "../include/utils.h"

/**
 * @brief Reads the input file and extracts information from the lines to build the graph
 *
 * @param char** vsrc (node-source)
 * @param char* path
 * @return Graph*
 */
GraphVector *read_graph_informations(char **vsrc, char *path)
{
    // Open the file
    FILE *fp = fopen(path, "r");

    if (fp == NULL)
    {
        perror("SOURCE FILE NOT FOUND!\n");
        exit(1);
    }

    // Get the file's first line to define which node is the source
    char *current_line = NULL;
    size_t size = 0;

    getline(&current_line, &size, fp);
    *vsrc = strdup(current_line);

    // Get file's second line to calculate the node amount
    getline(&current_line, &size, fp);
    int nodes_amount = get_nodes_amount(current_line);

    // Create the graph from node amount
    GraphVector *graph_vector = graph_vector_create(nodes_amount);
    int i = 0;

    // Add info from first line to the graph
    graph_vector_add_edges(graph_vector, current_line, i);
    i++;

    // Repeat, getting the next line of the file and adding info to the graph until the file ends
    while (getline(&current_line, &size, fp) != -1)
    {
        graph_vector_add_edges(graph_vector, current_line, i);
        i++;
    }

    // Free memory allocated to read lines and close the file
    free(current_line);
    fclose(fp);

    return graph_vector;
}

/**
 * @brief Read the second line of the entry file and calculate how many nodes there are
 *
 * @param char* current_line
 * @return int
 */
int get_nodes_amount(char *current_line)
{
    // Initialize variables and make a copy from line. Then, break the line in the commas to get the info from nodes
    int nodes_amount = -1;
    char *aux = strdup(current_line);
    char *item = strtok(aux, ",");

    // For each step, if there is a new node, increment node amount
    while (item)
    {
        nodes_amount++;

        item = strtok(NULL, ",");
    }

    // Free memory allocated to line duplicate
    free(aux);

    return nodes_amount;
}

/**
 * @brief Receive a string with source-node's name and return its index
 *
 * @param char* name
 * @return int
 */
int get_number_id(char *name)
{
    int number;
    sscanf(name, "node_%d", &number);
    return number;
}

/**
 * Calculates the minimum path from one origin node to all nodes. Dijkstras algorithm iterates over the graph, analyzing the distance between the nodes. A distance vector is initialized with infinity distances and updated as the algorithm finds smaller distances. Furthertmore, a visited vector is used to mark nodes that are already part of the path. The inspiration to this code can be found in this tutorial: https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
 * @param Graph* graph The graph that contains the nodes informations.
 * @param int src The origin node of the paths to be calculated.
 * @param float* dist The vector of distances
 * @param int* path The vector that holds the minimum path
 * @returns The new vector of minimum paths from the origin node to all nodes.
 */
void djikstra(GraphVector *graph_vector, int src, float *dist, int *path)
{
    // Get the node amount and allocate memory to visited vector
    int nodeAmount = graph_vector_get_nodes_amount(graph_vector);
    int *visited = calloc(nodeAmount + 1, sizeof(int));

    for (int i = 0; i <= nodeAmount; i++)
    {
        // All the distances between a origin node and a destination node are initialized with infinity. This value is used in comparisons because it is big and any smaller distance is considered later in the algorithm
        dist[i] = INFINITY;
        path[i] = -1;
    }

    // The distance of the node to itself is 0
    dist[src] = 0.0;

    // For each node in graph, the algorithm iterates over the items, always getting the minimum
    for (int i = 0; i < nodeAmount - 1; i++)
    {
        // Get the nodes that aren't part of the path yet and find the minimum between them.
        int u = __get_min_distance(dist, visited, nodeAmount);

        // Mark the node as visited (part of the path)
        visited[u] = 1;

        // For each node in graph, repeat
        for (int i = 0; i < nodeAmount; i++)
        {
            // Get the distance between the node that is being analyzed and the current node
            float dist_v = graph_vector_get_distance(graph_vector, u, i);

            // If the current node hasn't been visited yet (hasn't been included in the path yet), the distance from this node to current node is not equal to zero (by doing it, bombs are just ignored) and the distance to the node being analyzed accumulated plus the distance between the two nodes is lower than current distance, include this node in the path
            if (visited[i] == 0 && dist_v && dist[u] != INFINITY && dist[u] + dist_v < dist[i])
            {
                dist[i] = dist[u] + dist_v;
                path[i] = u;
            }
        }
    }

    // Freeing memory of visited vector
    free(visited);
}

/**
 * @brief Find the min distance in the distances vector, considering just the nodes that haven't been visited yet
 *
 * @param float* dist
 * @param int* visited
 * @param int node_amount
 * @return int
 */
int __get_min_distance(float *dist, int *visited, int node_amount)
{
    // Initialize distance with the highest distance possible
    float min = INFINITY;
    int min_index;

    // For each node, if the node hasn't been visited yet and the current distance is lower than the minimum distance find until that moment, this min distance and its index are updated
    for (int i = 0; i < node_amount; i++)
    {
        if (visited[i] == 0 && dist[i] <= min)
        {
            min = dist[i];
            min_index = i;
        }
    }

    return min_index;
}

/**
 * @brief Printing the minimum path by creating a special structure
 *
 * @param int* path
 * @param float* dist
 * @param int src
 * @param int nodeAmount
 * @param char* file_path
 */
void print_shortest_path(int *path, float *dist, int src, int nodeAmount, char *file_path)
{
    // Allocate a vector of printers and initialize them with the distances found by Djikstra algorithm
    Printer **p_vector = printer_vector_create(src, dist, nodeAmount);

    // Sort printers vector by distances
    qsort(p_vector, nodeAmount, sizeof(Printer *), printer_compare);

    // Print the path from source node to all other nodes
    printer_print_path(p_vector, src, nodeAmount, path, file_path);

    // Free the memory allocated to printers vector
    printer_free(p_vector, nodeAmount);
}