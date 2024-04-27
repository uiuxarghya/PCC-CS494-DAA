#include <stdbool.h>
#include <stdio.h>

// Function to display the chessboard
void display(int N, int board[N][N]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (board[i][j] == 0)
        printf(". ");  // Print '.' if there's no queen
      else
        printf("Q ");  // Print 'Q' if there's a queen
    }
    printf("\n");
  }
  printf("\n");
}

// Function to check if placing a queen at board[row][col] is safe
bool isSafe(int N, int board[N][N], int row, int col) {
  // Check if there's any queen in the same row
  for (int i = 0; i < col; i++) {
    if (board[row][i]) return false;
  }
  // Check if there's any queen on the upper left diagonal
  for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
    if (board[i][j]) return false;
  }
  // Check if there's any queen on the lower left diagonal
  for (int i = row, j = col; j >= 0 && i < N; i++, j--) {
    if (board[i][j]) return false;
  }
  return true;
}

// Recursive function to solve N-Queens problem
bool solveNQueensUtil(int N, int board[N][N], int col) {
  // If all queens are placed, print the solution
  if (col == N) {
    display(N, board);
    return true;
  }
  bool res = false;
  // Try placing queen in each row of the current column
  for (int i = 0; i < N; i++) {
    if (isSafe(N, board, i, col)) {
      // Place queen at board[i][col]
      board[i][col] = 1;
      // Recur to place queens in remaining columns
      res = solveNQueensUtil(N, board, col + 1) || res;
      // If placing queen at board[i][col] doesn't lead to a solution, backtrack
      board[i][col] = 0;  // backtrack
    }
  }
  return res;
}

// Function to solve N-Queens problem and print the solutions
bool solveNQueens(int N) {
  int board[N][N];
  // Initialize the board to all zeros
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++) board[i][j] = 0;

  // Start solving from the first column
  if (!solveNQueensUtil(N, board, 0)) {
    printf("No Possible Solution\n");
    return false;
  }
  return true;
}

int main() {
  int N;
  printf("Enter the value of N : ");
  scanf("%d", &N);

  // Check for valid input
  if (N <= 0) {
    printf("Invalid Input\n");
    return 0;
  }

  // Solve N-Queens problem for input N
  solveNQueens(N);
  return 0;
}
