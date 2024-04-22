
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct graph
{
  int V;     // Number of vertices
  int **adj; // Adjacency matrix
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

int findMinKey(int key[], bool mstSet[], int V)
{
  int min = -1;
  for (int v = 0; v < V; v++)
  {
    if (!mstSet[v] && (min == -1 || key[v] < key[min]))
    {
      min = v;
    }
  }
  return min;
}

void primMST(Graph *graph)
{
  int parent[graph->V];
  int key[graph->V];
  bool mstSet[graph->V];

  for (int i = 0; i < graph->V; i++)
  {
    key[i] = 10000; // Initialize key with a large value (representing infinity)
    mstSet[i] = false;
  }

  key[0] = 0;
  parent[0] = -1;

  for (int count = 0; count < graph->V - 1; count++)
  {
    int u = findMinKey(key, mstSet, graph->V);
    mstSet[u] = true;

    for (int v = 0; v < graph->V; v++)
    {
      if (graph->adj[u][v] && !mstSet[v] && graph->adj[u][v] < key[v])
      {
        parent[v] = u;
        key[v] = graph->adj[u][v];
      }
    }
  }

  printMST(parent, key, graph->V);
}

int main()
{
  Graph graph;
  printf("Enter the number of vertices: ");
  scanf("%d", &graph.V);

  printf("Enter the number of edges: ");
  int edges;
  scanf("%d", &edges);

  graph.adj = (int **)malloc(graph.V * sizeof(int *));
  for (int i = 0; i < graph.V; i++)
  {
    graph.adj[i] = (int *)malloc(graph.V * sizeof(int));
    for (int j = 0; j < graph.V; j++)
    {
      graph.adj[i][j] = 0; // Initialize all edges to 0
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
    graph.adj[src][dest] = weight;
    graph.adj[dest][src] = weight; // Assuming undirected graph
  }

  primMST(&graph);
  free(graph.adj);
  return 0;
}
