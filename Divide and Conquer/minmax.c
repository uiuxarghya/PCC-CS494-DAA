#include <stdio.h>

void findMinMaxDC(int arr[],int start, int end, int *min, int *max){
  
  if(start == end) {
    *min = arr[start];
    *max = arr[end];
    return;
  }
    
   
  int mid = (start + end)/2;
  int min1, max1, min2, max2;
  
  findMinMaxDC(arr, start, mid, &min1, &max1);
  findMinMaxDC(arr, mid+1, end, &min2, &max2);
  
  *min = min1 < min2 ? min1 : min2;
  *max = max1 > max2 ? max1 : max2;
}

void main() {
  int n;
  printf("Enter the number of elements: ");
  scanf("%d",&n);
  
  int arr[n];
  
  for(int i = 0; i<n;i++) {
    printf("Enter the value of arr[%d]: ",i);
    scanf("%d",&arr[i]);
  }
  
  int min, max;
  
  findMinMaxDC(arr,0,n-1,&min,&max);
  
  printf("\nMinimum: %d ",min);
  printf("\nMaximum: %d ",max);
  
  printf("\n");
}
  
