#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100

typedef struct graph
{
  int vertices;
  bool adj[MAX][MAX];
} Graph;

Graph *createGraph(int vertices)
{
  Graph *g = (Graph *)malloc(sizeof(Graph));
  g->vertices = vertices;
  int i, j;
  for (i = 0; i < vertices; i++)
  {
    for (j = 0; j < vertices; j++)
    {
      g->adj[i][j] = false;
    }
  }
  return g;
}

void addEdge(Graph *g, char src, char dest)
{
  g->adj[src - 'A'][dest - 'A'] = true;
}

void DFS(Graph *g, bool visited[MAX], char start)
{
  char current = start;
  printf("%c ", current);
  visited[current - 'A'] = true;
  for (int i = 0; i < g->vertices; i++)
  {
    if (g->adj[current - 'A'][i] && !visited[i])
      DFS(g, visited, i + 'A');
  }
}

int main()
{
  int vertices, edges, i;
  char src, dest, start;

  printf("\nEnter the number of vertices : ");
  scanf("%d", &vertices);

  Graph *g = createGraph(vertices);

  printf("\nEnter the number of edges: ");
  scanf("%d", &edges);

  printf("\n");

  for (i = 0; i < edges; i++)
  {
    printf("Enter the value of edges (source, destination) form (A to Z): ");
    scanf(" %c %c", &src, &dest);
    addEdge(g, src, dest);
  }

  printf("\nEnter the starting vertex (A to Z): ");
  scanf(" %c", &start);

  bool visited[MAX];
  for (i = 0; i < vertices; i++)
    visited[i] = false;

  printf("\nDFS Traversal: ");
  DFS(g, visited, start);

  printf("\n");
  return 0;
}
