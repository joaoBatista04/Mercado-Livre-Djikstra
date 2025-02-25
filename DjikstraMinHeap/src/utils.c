#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "../include/pq.h"
#include "../include/printer.h"
#include "../include/utils.h"

/**
 * @brief Reads the input file and extracts information from the lines to build the graph
 *
 * @param char** vsrc (node-source)
 * @param char* path
 * @return Graph*
 */
Graph *read_graph_informations(char **vsrc, char *path)
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
    Graph *graph = graph_create(nodes_amount);
    int i = 0;

    // Add info from first line to the graph
    graph_add_edges(graph, current_line, i);
    i++;

    // Repeat, getting the next line of the file and adding info to the graph until the file ends
    while (getline(&current_line, &size, fp) != -1)
    {
        graph_add_edges(graph, current_line, i);
        i++;
    }

    // Free memory allocated to read lines and close the file
    free(current_line);
    fclose(fp);

    return graph;
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
 * Calculates the minimum path from one origin node to all nodes. Dijkstras algorithm iterates over the graph, analyzing the distance between the nodes. A distance vector is initialized with infinity distances and updated as the algorithm finds smaller distances. Furthertmore, a visited vector is used to avoid analyzing nodes that was already analyzed. The inspiration to this code can be found in this video (https://www.youtube.com/watch?v=NyrHRNiRpds) and in the first variation described in the fifth page of the following document (https://drops.dagstuhl.de/storage/00lipics/lipics-vol226-fun2022/LIPIcs.FUN.2022.8/LIPIcs.FUN.2022.8.pdf)
 * @param Graph* graph The graph that contains the nodes informations.
 * @param int src The origin node of the paths to be calculated.
 * @param float* dist The vector of distances
 * @param int* path The vector that holds the minimum path
 * @returns The new vector of minimum paths from the origin node to all nodes.
 */
void djikstra(Graph *graph, int src, float *dist, int *path)
{
    // Get the node amount and allocate memory to visited vector
    int nodeAmount = graph_get_nodes_amount(graph);
    int *visited = calloc(nodeAmount + 1, sizeof(int));

    for (int i = 0; i <= nodeAmount; i++)
    {
        // All the distances between a origin node and a destination node are initialized with infinity. This value is used in comparisons because it is big and any smaller distance is considered later in the algorithm
        dist[i] = INFINITY;
        path[i] = -1;
    }

    // The distance of the node to itself is 0
    dist[src] = 0.0;

    // Initialing the priority queue
    PQ *pq = pq_init(nodeAmount);

    // Inserting the initial node (the origin node) into the priority queue, with 0.0 priority (the lowest value)
    Node *src_node = node_create(src, INFINITY);
    node_set_weight(src_node, 0.0);
    pq_insert(pq, src_node);

    // While the priority queue isn't empty, the algorithm iterates over the priority queue items, always getting the minimum
    while (!pq_empty(pq))
    {
        // Getting the miminum item of the priority queue and checking it as visited
        Node *u = pq_delete_min(pq);
        int u_id = node_get_id(u);
        visited[u_id] = 1;

        // Getting the node and its connections
        Node *v = graph_get_node(graph, u_id);

        // While the node has connections, the loop follows. It means that the algorithm will analyze all edges that start in origin node and end in its connections
        while (v)
        {
            // If the node wasn't visited, than the algorithm goes to that node
            if (visited[node_get_id(v)] == 0)
            {
                float newWeight;
                int v_id = node_get_id(v);
                float v_weight = node_get_weight(v);

                // Calculating the weight of the distance of current node to origin node
                newWeight = dist[u_id] + v_weight;

                // If this distance is smaller than the distance registered in the distance vector, the new distance will be stored
                if (newWeight < dist[v_id])
                {
                    // The new distance is stored and the path to source is updated
                    dist[v_id] = newWeight;
                    path[v_id] = u_id;

                    // Check if there is a node in the priority queue with the same ID of the current node that the algorithm is analyzing
                    if (pq_contains(pq, v_id))
                    {
                        // In positive case, a new item isn't created. Instead of that, the algorithm just update the weight of that item
                        pq_decrease_key(pq, v_id, newWeight);
                    }
                    else
                    {
                        // In negative case, a new item is created with the ID of the node that the algorithm is analyzing and its distance to the origin
                        Node *newPQNode = node_create(v_id, newWeight);
                        pq_insert(pq, newPQNode);
                    }
                }
            }
            // Get the next connection/edge of the node
            v = node_get_next(v);
        }

        // If the node isn't NULL, the memory allocated to it is freed
        if (u)
        {
            node_destroy(u);
        }
    }
    // Freeing the memory allocated to visited nodes vector and priority queue
    free(visited);
    pq_destroy(pq);
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
    Printer **p_vector = printer_vector_create(src, dist, nodeAmount + 1);

    // Sort printers vector by distances
    qsort(p_vector, nodeAmount + 1, sizeof(Printer *), printer_compare);

    // Print the path from source node to all other nodes
    printer_print_path(p_vector, src, nodeAmount, path, file_path);

    // Free the memory allocated to printers vector
    printer_free(p_vector, nodeAmount + 1);
}