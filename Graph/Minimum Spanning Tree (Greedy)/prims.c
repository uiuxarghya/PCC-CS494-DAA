
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct graph
{
  int V;     // Number of vertices
  int **adj; // Adjacency matrix to store weights of edges between each pair of vertices
} Graph;

void printMST(int parent[], int key[], int V)
{
  printf("\nMinimum Spanning Tree\n");
  printf("Edge \tWeight\n");
  for (int i = 1; i < V; i++)
  {
    printf("%c - %c \t%d\n", parent[i] + 'a', i + 'a', key[i]);
  }
}

int findMinKey(int key[], bool mstSet[], int V) //finds vertex (not included in MST) with minimum key 
{
  int min = -1;
  for (int v = 0; v < V; v++)
  {
    if (!mstSet[v] && (min == -1 || key[v] < key[min]))
    {
      min = v;
    }
  }
  return min; //return minimum vertex
}

void primMST(Graph *graph)
{
  int parent[graph->V]; // array to store parent of each vertex in MST
  int key[graph->V]; // array to weight of each vertex
  bool mstSet[graph->V]; // array to keep track of vertices included in the MST

  for (int i = 0; i < graph->V; i++)
  {
    key[i] = 10000; // Initialize key with a large value (representing infinity)
    mstSet[i] = false; // all vertices are initialized as not included (false)
  }

  key[0] = 0; // initialiazes key of starting vertex of MST to 0
  parent[0] = -1; // initializes its parent to -1 indicating it has no parent

  for (int count = 0; count < graph->V - 1; count++) // iterate V - 1 times to select V - 1 edges for the MST
  {
    int u = findMinKey(key, mstSet, graph->V); // finds vertex with minimum key value which is not included in MST
    mstSet[u] = true; // mark this vertex as included in the MST

    for (int v = 0; v < graph->V; v++) // finds the adjacent or neighbouring vertices of the current minimum vertex
    {
      // checks for 3 conditions
      // 1. whether there's an edge to an adjacent vertex ; 
      // 2. whether the edge between current vertex and adjacent vertex is added to MST
      // 3. whether the weight of the edge between them is less than the key value (which is originally initialized to 1000)
      if (graph->adj[u][v] && !mstSet[v] && graph->adj[u][v] < key[v])
      {
        parent[v] = u; // initialize the parent of the neighbouring vertex as the current vertex
        key[v] = graph->adj[u][v]; // update the key value from the adjacency matrix
      }
    }
  }

  printMST(parent, key, graph->V); // prints the MST
}

int main()
{
  Graph graph;
  printf("Enter the number of vertices: ");
  scanf("%d", &graph.V);

  printf("Enter the number of edges: ");
  int edges;
  scanf("%d", &edges);

  //Creates a graph.V * graph.V size adjacency matrix
  graph.adj = (int **)malloc(graph.V * sizeof(int *)); // initializes number of rows
  for (int i = 0; i < graph.V; i++)
  {
    graph.adj[i] = (int *)malloc(graph.V * sizeof(int));  // initializes number of columns
    for (int j = 0; j < graph.V; j++)
    {
      graph.adj[i][j] = 0; // Initialize weights of all edges to 0
    }
  }

  int src, dest;
  int weight;

  for (int i = 0; i < edges; i++)
  {
    char src_char, dest_char;
    printf("Enter the source, destination and weight : ");
    scanf(" %c %c %d", &src_char, &dest_char, &weight);
    src = src_char - 'a'; // Map to integer index
    dest = dest_char - 'a';
    graph.adj[src][dest] = weight; // initializes weight of edges between src and dest
    graph.adj[dest][src] = weight; // Assuming undirected graph
  }

  primMST(&graph);
  free(graph.adj);
  return 0;
}
