#include <stdio.h>
#include <string.h>
#include <limits.h>

int min(int d[], int i, int j, int n, int value[][n], int p[])
{
  if (i == j) {
    value[i][j] = 0;
    return 0;
  }
  else if (i < j) {
    if (value[i][j] != -1)
      return value[i][j];
    else {
      int k, x = INT_MAX, t;
      for (k=i; k<=j-1; k++) {
        t = min(d, i, k, n, value, p) + min(d, k+1, j, n, value, p) + d[i]*d[k+1]*d[j+1];
        if (x > t) {
          x = t;
          if (i==0 && j==n-1) {
            p[0]=i, p[1]=k, p[2]=k+1, p[3]=j;
          }
        }
      }
      value[i][j] = x;
      return x;
    }
  }
}

void main()
{
  int n, i, j;
  printf("Enter the number of values : ");
  scanf("%d", &n);

  int d[n]; //dimensions array

  for (i=0; i<n; i++) {
    printf("Enter value of d[%d] : ", i);
    scanf("%d", &d[i]);
  }

  int value[n-1][n-1];

  for (i=0; i<n-1; i++) {
    for (j=0; j<n-1; j++) {
      value[i][j] = -1;
    }
  }

  int p[4]; //parenthesis array
  int result = min(d, 0, 5, n-1, value, p);

  printf("\nMatrix Multiplication Table :\n");
  printf("\n");
  
  for (i=0; i<n-1; i++) {
    for (int j=0; j<n-1; j++) {
      printf("%d\t", value[i][j]);
    }
    printf("\n");
  }

  printf("\nMinimum number of multiplications : %d",value[0][n-2]);
  printf("\nParenthization : (%d - %d) * (%d - %d)", p[0], p[1], p[2], p[3]);
  
  printf("\n");
}

