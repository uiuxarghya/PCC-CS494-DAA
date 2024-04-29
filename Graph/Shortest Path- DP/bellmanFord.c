#include <stdio.h>
#include <limits.h>


// function to perform the bellman-ford algorithm
void bellmanFord(int graph[][3], int vertices, int edges, int distance[], int source)
{
    distance[source] = 0; // set the source distance to 0
    int count;

    for (count = 1; count < vertices; count++) // loop to relax all edges (vertices-1) times (different from Dijkstra's algorithm)
    {
        int i, u, v, wt;
        for (i = 0; i < edges; i++)
        {
            u = graph[i][0]; // start vertex of the edge
            v = graph[i][1]; // end vertex of the edge
            wt = graph[i][2]; // weight of the edge
            // distance[u] = shortest distance to vertex u
            // distance[v] = shortest distance to vertex v
            if (distance[u] != INT_MAX && (distance[u] + wt) < distance[v]) // relax the edge if possible
                distance[v] = distance[u] + wt;
        }
    }

    // Check for negative weight cycles
    for (int i = 0; i < edges; i++) // repeats the above same process one more time
    {
        int u = graph[i][0];
        int v = graph[i][1];
        int wt = graph[i][2];

        // if graph contains a negative weight cycle where weight value of edges just keeps on decreasing
        if (distance[u] != INT_MAX && distance[u] + wt < distance[v]) 
        {
            printf("Graph contains negative weight cycle\n"); // then it will display the following 
            return; // and come out of the loop
        }
    }
}

// function to print the shortest distances from the source to all other vertices
void printDistance(int distance[], int source, int vertices) 
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < vertices; i++)
        printf("%d\t\t%d\n", i, distance[i]);
}

int main()
{
    int vertices,edges;
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
    bellmanFord(graph, vertices, edges, distance, source); // run the bellman-ford algorithm
    printDistance(distance, source, vertices); // print the results
    return 0;
}
