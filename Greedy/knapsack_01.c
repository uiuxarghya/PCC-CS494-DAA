#include <stdio.h>
#include <string.h>

int max(int a, int b) {
  return (a>b)?a:b;
}

void find_added(int n, int weight, int w[], int dp[][weight+1], int added[]) {
  int i, j = weight, b=1, p, k;
  for(i=n; i>=1; i--) {
    if(dp[i-1][j] != dp[i][j]) {
      added[i-1] = 1;
      j = j - w[i-1];
    }
  }
}

int find_profit(int val[],int w[],int n,int weight,int dp[][weight+1]) {
  int i,j,x,y;
  for(i=0; i<=weight; i++) {
    dp[0][i] = 0;
  }
  for(i=1; i<=n; i++) {
    dp[i][0] = 0;
  }

  for(i=1; i<=n; i++) {
    for(j=1; j<=weight; j++) {
      if(j < w[i-1]) {
        dp[i][j] = dp[i-1][j];
      } else {
        x = dp[i-1][j];
        y = val[i-1] + dp[i-1][j-w[i-1]];
        dp[i][j] = max(x,y);
      }
    }
  }
  return dp[n][weight];
}

void input(int n, int val[],int w[]) {
  int i;
  printf("\nItem\t\tValue\tWeight\n");
  printf("------------------------------\n");
  for(i=0; i<n; i++) {
    printf("Item-%d :\t",i+1);
    scanf("%d\t%d",&val[i],&w[i]);
  }
}

void main() {
  int i,n,weight,profit;

  printf("Enter the number of items : ");
  scanf("%d",&n);
  int val[n], w[n];
  input(n,val,w);
  printf("\nEnter the capaccity of the knapsack : ");
  scanf("%d",&weight);

  int dp[n+1][weight+1];
  int added[n];
  memset(added,0,sizeof(added));

  profit = find_profit(val,w,n,weight,dp);
  find_added(n,weight,w,dp,added);

  printf("\nThe Maximum profit would be : %d\n",profit);
  printf("Items added to the knapsack are : ");
  for(i=0; i<n; i++) {
    if(added[i] != 0) {
      printf("%d,\t",i+1);
    }
  }
  printf("\n");

}
