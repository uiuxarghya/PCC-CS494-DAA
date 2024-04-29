#include <stdio.h>
#include <stdbool.h>
#define N 4

int getInvCount(int arr[])
{
  int inv_count = 0;
  for (int i = 0; i < N * N - 1; i++)
  {
    for (int j = i + 1; j < N * N; j++)
    {
      // Only count inversions for non-zero elements
      if (arr[j] != 0 && arr[i] != 0 && arr[i] > arr[j])
        inv_count++;
    }
  }
  return inv_count;
}

int findXPosition(int puzzle[N][N])
{
  // Find row position of the blank tile (0) from the bottom of the grid
  for (int i = N - 1; i >= 0; i--)
    for (int j = N - 1; j >= 0; j--)
      if (puzzle[i][j] == 0)
        return N - i;
  return -1;
}

bool isSolvable(int puzzle[N][N])
{
  int arr[N * N], k = 0;
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      arr[k++] = puzzle[i][j];

  int invCount = getInvCount(arr);
  // Check solvability rules based on the grid size (N)
  if (N % 2 == 1) // Odd grid
    return invCount % 2 == 0;
  else // Even grid
  {
    int pos = findXPosition(puzzle);
    if (pos % 2 == 1)
      return invCount % 2 == 0;
    else
      return invCount % 2 == 1;
  }
}

int main()
{
  int puzzle[N][N];

  printf("Enter the puzzle in row-major order (use zero for the blank space):\n");
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      scanf("%d", &puzzle[i][j]);
    }
  }

  printf("\nThe given puzzle is : ");
  printf("%s\n", isSolvable(puzzle) ? "Solvable" : "Not Solvable");
  return 0;
}
