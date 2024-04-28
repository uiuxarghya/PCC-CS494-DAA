#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 100
#define MAX_EDGES 100

int vertices, edges;

// Structure to represent an edge
struct Edge {
    char source, destination;
    int weight;
};

// Function to perform the Bellman-Ford algorithm
void bellmanFord(struct Edge edge[], int distance[], char source) {
    distance[source - 'A'] = 0; // Set distance to source as 0

    // Relax all edges |V| - 1 times
    for (int i = 0; i < vertices - 1; i++) {
        for (int j = 0; j < edges; j++) {
            char u = edge[j].source;
            char v = edge[j].destination;
            int wt = edge[j].weight;
            if (distance[u - 'A'] != INT_MAX && distance[u - 'A'] + wt < distance[v - 'A'])
                distance[v - 'A'] = distance[u - 'A'] + wt;
        }
    }

    // Check for negative weight cycles
    for (int i = 0; i < edges; i++) {
        char u = edge[i].source;
        char v = edge[i].destination;
        int wt = edge[i].weight;
        if (distance[u - 'A'] != INT_MAX && distance[u - 'A'] + wt < distance[v - 'A']) {
            printf("Graph contains negative weight cycle\n");
            return;
        }
    }
}

// Function to print the shortest distances from source
void printDistance(int distance[], char source) {
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < vertices; i++) {
        printf("%c\t\t%d\n", 'A' + i, distance[i]);
    }
}

int main() {
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    struct Edge edge[MAX_EDGES];
    int distance[MAX_VERTICES];

    printf("Enter the source, destination, and weight for each edge:\n");
    for (int i = 0; i < edges; i++) {
        scanf(" %c %c %d", &edge[i].source, &edge[i].destination, &edge[i].weight);
    }

    // Initialize distances
    for (int i = 0; i < vertices; i++) {
        distance[i] = INT_MAX;
    }

    char source;
    printf("Enter the source vertex: ");
    scanf(" %c", &source);

    bellmanFord(edge, distance, source);

    printDistance(distance, source);

    return 0;
}
