#include <stdbool.h>
#include <stdio.h>

void display(int N, int board[N][N]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (board[i][j] == 0)
        printf(". ");
      else
        printf("Q ");
    }
    printf("\n");
  }
  printf("\n");
}

bool isSafe(int N, int board[N][N], int row, int col) {
  for (int i = 0; i < col; i++) {
    if (board[row][i]) return false;
  }
  for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
    if (board[i][j]) return false;
  }
  for (int i = row, j = col; j >= 0 && i < N; i++, j--) {
    if (board[i][j]) return false;
  }
  return true;
}

bool solveNQueensUtil(int N, int board[N][N], int col) {
  if (col == N) {
    display(N, board);
    return true;
  }
  bool res = false;
  for (int i = 0; i < N; i++) {
    if (isSafe(N, board, i, col)) {
      board[i][col] = 1;
      res = solveNQueensUtil(N, board, col + 1) || res;
      board[i][col] = 0;  // backtrack
    }
  }
  return res;
}

bool solveNQueens(int N) {
  int board[N][N];
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++) board[i][j] = 0;

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

  if (N <= 0) {
    printf("Invalid Input\n");
    return 0;
  }

  solveNQueens(N);
  return 0;
}
