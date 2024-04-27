#include <stdio.h>
#include <limits.h>

int vertices, edges;

// function to perform the bellman-ford algorithm
void bellmanFord(int graph[edges][3], int edges, int distance[], int source)
{
    distance[source] = 0; // set the source distance to 0
    int count;
    for (count = 1; count < vertices; count++) // loop to relax all edges (vertices-1) times
    {
        int i, u, v, wt;
        for (i = 0; i < edges; i++)
        {
            u = graph[i][0]; // start vertex of the edge
            v = graph[i][1]; // end vertex of the edge
            wt = graph[i][2]; // weight of the edge
            // relax the edge if possible
            if (distance[u] != INT_MAX && (distance[u] + wt) < distance[v])
                distance[v] = distance[u] + wt;
        }
    }
}

// function to print the shortest distances from the source to all other vertices
void printDistance(int distance[], int source)
{
    int i;
    printf("\nThe Shortest Distances from Source %d are : \n", source);
    printf("Vertex\tDistance\n");
    for (i = 0; i < vertices; i++)
    {
        if (i == source) // skip printing the source itself
            continue;
        printf("%d     \t%d\n", i, distance[i]); // print the vertex and its distance from the source
    }
}

int main()
{
    printf("Enter the no. of Vertices : ");
    scanf("%d", &vertices); // input number of vertices
    int distance[vertices];
    int source, i;
    printf("Enter no. of Edges : ");
    scanf("%d", &edges); // input number of edges
    int graph[edges][3];
    printf("Enter the Adjacency List (Source, Destination and Cost) : \n");
    for (i = 0; i < edges; i++) // input each edge including its source, destination, and weight
        scanf("%d %d %d", &graph[i][0], &graph[i][1], &graph[i][2]);
    for (i = 0; i < vertices; i++)
        distance[i] = INT_MAX; // initialize distances to infinity
    printf("Enter the Source vertex : ");
    scanf("%d", &source); // input the source vertex
    bellmanFord(graph, edges, distance, source); // run the bellman-ford algorithm
    printDistance(distance, source); // print the results
    return 0;
}
