#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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
  g->adj[src - 'a'][dest - 'a'] = true;
}

void BFS(Graph *g, char start)
{
  bool visited[MAX];
  char queue[MAX];
  int i, front = 0, rear = 0;
  for (i = 0; i < g->vertices; i++)
  {
    visited[i] = false;
  }
  visited[start - 'a'] = true;
  queue[rear++] = start;
  while (front < rear)
  {
    start = queue[front++];
    printf("%c ", start);
    for (i = 0; i < g->vertices; i++)
    {
      if (g->adj[start - 'a'][i] == true && visited[i] == false)
      {
        visited[i] = true;
        queue[rear++] = i + 'a';
      }
    }
  }
}

int main()
{
  int vertices, edges, i;
  char src, dest, start;

  printf("\nEnter the number of vertices: ");
  scanf("%d", &vertices);

  Graph *g = createGraph(vertices);

  printf("\nEnter the number of edges: ");
  scanf("%d", &edges);

  printf("\n");

  for (i = 0; i < edges; i++)
  {
    printf("Enter the value of edges (source, destination) form (a to z): ");
    scanf(" %c %c", &src, &dest);
    addEdge(g, src, dest);
  }

  printf("\nEnter the starting vertex (a to z): ");
  scanf(" %c", &start);

  printf("\nBFS Traversal: ");
  BFS(g, start);
  
  printf("\n");
  return 0;
}
