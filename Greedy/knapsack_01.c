#include <stdio.h>
#include <string.h>

// Function to find the maximum of two integers
int max(int a, int b) {
  return (a > b) ? a : b;
}

// Function to find the items added to the knapsack
void find_added(int n, int weight, int w[], int dp[][weight + 1], int added[]) {
  int i, j = weight;
  
  // Start from the last item and iterate backward
  for (i = n; i >= 1; i--) {
    // If the current item is added to the knapsack
    if (dp[i - 1][j] != dp[i][j]) {
      added[i - 1] = 1; // Mark the item as added
      j = j - w[i - 1]; // Update the remaining weight
    }
  }
}

// Function to find the maximum profit
int find_profit(int val[], int w[], int n, int weight, int dp[][weight + 1]) {
  int i, j, x, y;
  
  // Initialize the first row and column of the dp table
  for (i = 0; i <= weight; i++) {
    dp[0][i] = 0;
  }
  for (i = 1; i <= n; i++) {
    dp[i][0] = 0;
  }

  // Fill the dp table
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= weight; j++) {
      if (j < w[i - 1]) {
        dp[i][j] = dp[i - 1][j];
      } else {
        x = dp[i - 1][j];
        y = val[i - 1] + dp[i - 1][j - w[i - 1]];
        dp[i][j] = max(x, y);
      }
    }
  }
  return dp[n][weight]; // Return the maximum profit
}

// Function to input values and weights of items
void input(int n, int val[], int w[]) {
  int i;
  printf("\nItem\t\tValue\tWeight\n");
  printf("------------------------------\n");
  for (i = 0; i < n; i++) {
    printf("Item-%d :\t", i + 1);
    scanf("%d\t%d", &val[i], &w[i]);
  }
}

// Main function
void main() {
  int i, n, weight, profit;

  printf("Enter the number of items : ");
  scanf("%d", &n);
  int val[n], w[n];
  input(n, val, w);
  printf("\nEnter the capacity of the knapsack : ");
  scanf("%d", &weight);

  int dp[n + 1][weight + 1]; // DP table
  int added[n]; // Array to store information about items added to knapsack
  memset(added, 0, sizeof(added)); // Initialize added array with zeros

  // Calculate maximum profit and items added to knapsack
  profit = find_profit(val, w, n, weight, dp);
  find_added(n, weight, w, dp, added);

  // Print results
  printf("\nThe Maximum profit would be : %d\n", profit);
  printf("Items added to the knapsack are : ");
  for (i = 0; i < n; i++) {
    if (added[i] != 0) {
      printf("%d,\t", i + 1); // Print index of items added to knapsack
    }
  }
  printf("\n");
}
