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
  Graph *graph = (Graph *)malloc(sizeof(Graph));
  graph->V = V;
  graph->E = E;
  graph->edges = (Edge *)malloc(E * sizeof(Edge));
  return graph;
}

void merge(Edge arr[], int l, int m, int r) {
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

  Edge L[n1], R[n2];

  for (i = 0; i < n1; i++) L[i] = arr[l + i];
  for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

  i = 0;
  j = 0;
  k = l;
  while (i < n1 && j < n2) {
    if (L[i].weight <= R[j].weight) {
      arr[k] = L[i++];
    } else {
      arr[k] = R[j++];
    }
    k++;
  }

  while (i < n1) {
    arr[k++] = L[i++];
  }

  while (j < n2) {
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

int find(int parent[], int i) {
  if (parent[i] == -1) return i;
  return find(parent, parent[i]);
}

void unionSets(int parent[], int x, int y) {
  int xset = find(parent, x);
  int yset = find(parent, y);
  if (xset != yset) parent[xset] = yset;
}

void kruskalMST(Graph *graph) {
  int V = graph->V;
  Edge result[V];
  int e = 0, i = 0;

  mergeSort(graph->edges, 0, graph->E - 1);

  int *parent = (int *)malloc(V * sizeof(int));

  for (i = 0; i < V; i++) parent[i] = -1;

  i = 0;

  while (e < V - 1 && i < graph->E) {
    Edge next_edge = graph->edges[i++];

    int x = find(parent, next_edge.src - 'A');
    int y = find(parent, next_edge.dest - 'A');

    if (x != y) {
      result[e++] = next_edge;
      unionSets(parent, x, y);
    }
  }

  printf("\nMinimum Spanning Tree:\n");
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

  Graph *graph = createGraph(V, E);

  for (int i = 0; i < E; i++) {
    printf("Enter value of edge %d (src, dest, weight): ", i + 1);
    scanf(" %c %c %d", &graph->edges[i].src, &graph->edges[i].dest,
          &graph->edges[i].weight);
  }

  kruskalMST(graph);

  return 0;
}
