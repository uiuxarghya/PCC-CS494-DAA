#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

int vertices;

// function to perform the dijkstra's algorithm
void dijkstra(int graph[vertices][vertices], bool final[], int distance[], int predecessor[], int source)
{
    distance[source - 1] = 0; // set the distance of the source vertex to itself as 0
    int count;
    for (count = 0; count < vertices - 1; count++)
    {
        int min = INT_MAX, index = -1, i;
        // find the vertex with the minimum distance which has not been finalized
        for (i = 0; i < vertices; i++)
        {
            if (!final[i] && distance[i] < min)
            {
                index = i;
                min = distance[i];
            }
        }
        final[index] = true; // mark the vertex as finalized

        // update the distance of the adjacent vertices of the selected vertex
        for (i = 0; i < vertices; i++)
        {
            if (graph[index][i] != 0 && !final[i] && (distance[index] + graph[index][i] < distance[i]))
            {
                distance[i] = distance[index] + graph[index][i];
                predecessor[i] = index; // set the predecessor for the vertex
            }
        }
    }
}

// function to print the shortest path from the source to a vertex
void printPath(int predecessor[], int v, int source)
{
    if (v == source - 1)
    {
        printf("%d ", source);
        return;
    }
    printPath(predecessor, predecessor[v], source);
    printf("%d ", v + 1);
}

// function to print the distances and paths from the source to all other vertices
void printDistance(int distance[], int predecessor[], int source)
{
    int i;
    printf("Vertex\tDistance\tPath\n");
    for (i = 0; i < vertices; i++)
    {
        if (i == source - 1)
            continue;
        printf("%d\t%d\t\t", i + 1, distance[i]);
        printPath(predecessor, i, source);
        printf("\n");
    }
}

int main()
{
    printf("Enter the no. of vertices : ");
    scanf("%d", &vertices); // input the number of vertices
    int graph[vertices][vertices];
    printf("Enter the Adjacency Matrix : \n");
    int row, col, i, source;
    // input the adjacency matrix
    for (row = 0; row < vertices; row++)
    {
        for (col = 0; col < vertices; col++)
        {
            scanf("%d", &graph[row][col]);
        }
    }

    bool final[vertices]; // keeps track of vertices for which the shortest path is already found
    int distance[vertices]; // holds the shortest distance from source to each vertex
    int predecessor[vertices]; // stores the predecessor of each vertex in the path

    for (i = 0; i < vertices; i++)
    {
        final[i] = false;
        distance[i] = INT_MAX; // initialize distances as infinite
        predecessor[i] = -1; // initialize predecessors
    }

    printf("Enter the Source vertex : ");
    scanf("%d", &source); // input the source vertex
    dijkstra(graph, final, distance, predecessor, source); // call the dijkstra function
    printDistance(distance, predecessor, source); // print the distances and paths
    return 0;
}
