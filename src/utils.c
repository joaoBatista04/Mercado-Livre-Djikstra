#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/pq.h"
#include "../include/printer.h"
#include "../include/utils.h"

Graph *read_graph_informations(char **vsrc, char *path)
{
    FILE *fp = fopen(path, "r");

    if (fp == NULL)
    {
        perror("SOURCE FILE NOT FOUND!\n");
        exit(1);
    }

    char *current_line = NULL;
    size_t size = 0;

    getline(&current_line, &size, fp);
    *vsrc = strdup(current_line);

    getline(&current_line, &size, fp);
    int nodes_amount = get_nodes_amount(current_line);

    Graph *graph = graph_create(nodes_amount);

    graph_add_edges(graph, current_line);
    while (getline(&current_line, &size, fp) != -1)
    {
        graph_add_edges(graph, current_line);
    }

    free(current_line);
    fclose(fp);

    return graph;
}

int get_nodes_amount(char *current_line)
{
    int nodes_amount = -1;
    char *aux = strdup(current_line);
    char *item = strtok(aux, ",");

    while (item)
    {
        nodes_amount++;

        item = strtok(NULL, ",");
    }

    free(aux);

    return nodes_amount;
}

int get_number_id(char *name)
{
    int number;
    sscanf(name, "node_%d", &number);
    return number;
}

void djikstra(Graph *graph, int src, float *dist, int *path)
{
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
                    // The new distance is stored
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

void print_shortest_path(int *path, float *dist, int src, int nodeAmount, char *file_path)
{
    Printer **p_vector = printer_vector_create(src, dist, nodeAmount + 1);

    qsort(p_vector, nodeAmount + 1, sizeof(Printer *), printer_compare);

    printer_print_path(p_vector, src, nodeAmount, path, file_path);

    printer_free(p_vector, nodeAmount + 1);
}