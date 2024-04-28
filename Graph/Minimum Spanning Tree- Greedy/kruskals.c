#include <stdio.h>
#include <stdlib.h>

typedef struct edge {
  char src, dest;
  int weight;
} Edge;

typedef struct graph {
  int V, E;
  Edge *edges;
} Graph;

Graph *createGraph(int V, int E) {
  Graph *graph = (Graph *)malloc(sizeof(Graph));  // stores the graph
  graph->V = V;
  graph->E = E;
  graph->edges = (Edge *)malloc(E * sizeof(Edge));  // stores the edges of the graph, forms an array of E number of edges
  return graph;
}

void merge(Edge arr[], int l, int m, int r) {
  int i, j, k; // counters for iterating over the left and right halves of the array
  int n1 = m - l + 1; // sizes of the two halves of the array
  int n2 = r - m; // sizes of the two halves of the array

  Edge L[n1], R[n2]; // temporary arrays to store the left and right halves of the array

  for (i = 0; i < n1; i++) L[i] = arr[l + i]; // copies the left half of the array to L
  for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j]; // copies the right half of the array to R

  i = 0; // initializes the counters
  j = 0; // initializes the counters
  k = l; // initializes the counters
  while (i < n1 && j < n2) {
    if (L[i].weight <= R[j].weight) { // compares the weights of the edges in the left and right halves
      arr[k] = L[i++]; // copies the edge with the smaller weight to the original array
    } else {
      arr[k] = R[j++]; // copies the edge with the smaller weight to the original array
    }
    k++;
  }

  while (i < n1) { // copies the remaining elements of the left half to the original array
    arr[k++] = L[i++];
  }

  while (j < n2) { // copies the remaining elements of the right half to the original array
    arr[k++] = R[j++];
  }
}

void mergeSort(Edge arr[], int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
  }
}

// recursively iterates to find the parent element of i whose value is still -1
int find(int parent[], int i)
{
  if (parent[i] == -1)
    return i;
  return find(parent, parent[i]);
}

void unionSets(int parent[], int x, int y) {
  int xset = find(parent, x);  // finds root of representative element x
  int yset = find(parent, y);  // finds root of representative element y

  // if they do not belong to the same set
  // parent of one root is updated to point to the other root ;
  // merges the two sets ; here yset becomes the new parent
  if (xset != yset)
    parent[xset] = yset;
}

void kruskalMST(Graph *graph) {
  int V = graph->V;  // stores no. of vertices of graph in V
  Edge result[V];    // array to store edges of MST
  int e = 0;         // counter for number of edges added to MST
  int i = 0;         // counter for iterating over the sorted edges

  mergeSort(graph->edges, 0, graph->E - 1); // sorts the edges of the graph (lb=0 ; ub=edges-1)

  int *parent = (int *)malloc(V * sizeof(int)); // stores parent of all vertices

  for (i = 0; i < V; i++) // initializes all the parents to -1 at first
    parent[i] = -1;

  i = 0;

  while (e < V - 1 && i < graph->E) // runs until either the MST is formed (e reaches V - 1) or all edges are processed
  {
    Edge next_edge = graph->edges[i++]; // retrieves next edges from sorted list (the 1st edge initially as i=0)

    int x = find(parent, next_edge.src - 'A'); // find root parent or representative element of source vertex
    int y = find(parent, next_edge.dest - 'A'); // find root parent or representative element of destination vertex

    // if x==y, then src and dest belongs to the same set, which means they form a cycle which cannot be added to the MST
    if (x != y)
    {
      result[e++] = next_edge;  // edge added to MST
      unionSets(parent, x, y);
    }
  }

  printf("\nMinimum Spanning Tree:\n");  // prints the MST
  printf("Edge\tWeight\n");
  for (i = 0; i < e; i++) {
    printf("%c - %c \t%d\n", result[i].src, result[i].dest, result[i].weight);
  }

  free(parent);
}

int main() {
  int V, E;
  printf("Enter the number of vertices: ");
  scanf("%d", &V);
  printf("Enter the number of edges: ");
  scanf("%d", &E);

  Graph *graph = createGraph(V, E);  // creates graph

  for (int i = 0; i < E; i++)  // inputs edges (src, dest, weight)
  {
    printf("Enter value of edge %d (src, dest, weight): ", i + 1);
    scanf(" %c %c %d", &graph->edges[i].src, &graph->edges[i].dest, &graph->edges[i].weight);
  }

  kruskalMST(graph);

  return 0;
}
