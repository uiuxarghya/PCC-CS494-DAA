#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// A utility function to check if the current color assignment is safe for vertex v
bool isSafe(int v, bool **graph, int *color, int c, int V)
{
  for (int i = 0; i < V; i++)
  {
    if (graph[v][i] && c == color[i])
    {
      return false;
    }
  }
  return true;
}

// Utility function to print solution
void printSolution(int *color, int V)
{
  printf("\nSolution Exists:\nFollowing are the assigned colors: ");
  for (int i = 0; i < V; i++)
  {
    printf("%d ", color[i]);
  }
  printf("\n");
}

// Recursive utility function to solve m coloring problem
bool graphColoringUtil(bool **graph, int m, int *color, int v, int V)
{
  if (v == V)
  {
    return true;
  }

  for (int c = 1; c <= m; c++)
  {
    if (isSafe(v, graph, color, c, V))
    {
      color[v] = c;
      if (graphColoringUtil(graph, m, color, v + 1, V))
      {
        return true;
      }
      color[v] = 0;
    }
  }
  return false;
}

// Function to find the chromatic number of the graph
int findChromaticNumber(bool **graph, int V)
{
  int *color = (int *)malloc(V * sizeof(int));

  for (int m = 1; m <= V; m++)
  {
    for (int i = 0; i < V; i++)
    {
      color[i] = 0;
    }

    if (graphColoringUtil(graph, m, color, 0, V))
    {
      printSolution(color, V);
      free(color);
      return m;
    }
  }

  free(color);
  return V; // In worst case, every vertex has a different color
}

int main()
{
  int V;
  printf("Enter the number of vertices: ");
  scanf("%d", &V);

  bool **graph = (bool **)malloc(V * sizeof(bool *));
  for (int i = 0; i < V; i++)
  {
    graph[i] = (bool *)malloc(V * sizeof(bool));
  }

  printf("Enter the adjacency matrix (as 0s and 1s):\n");
  for (int i = 0; i < V; i++)
  {
    for (int j = 0; j < V; j++)
    {
      int temp;
      scanf("%d", &temp); // Read into a temporary int variable.

      graph[i][j] = (temp != 0);
    }
  }

  int chromaticNumber = findChromaticNumber(graph, V);
  printf("The chromatic number of the graph is %d.\n", chromaticNumber);

  free(graph);
  return 0;
}
