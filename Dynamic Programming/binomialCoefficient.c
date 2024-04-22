#include <stdio.h>

int binarySearch(int arr[], int x, int low, int high) {
  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (arr[mid] == x)  // element found at mid
      return mid;

    if (arr[mid] < x)  // element is greater
      low = mid + 1;
    else  // element is smaller
      high = mid - 1;
  }

  return -1;  // element not found
}

int main(void) {
  int n, i, num;

  printf("Enter your array length: ");
  scanf("%d", &n);

  int arr[n];  // declare array

  printf("\nEnter values in ascending order\n");
  for (i = 0; i < n; i++) {
    printf("Enter the value of arr[%d]: ", i);
    scanf("%d", &arr[i]);
  }

  printf("\nEnter the element to search: ");
  scanf("%d", &num);

  int result = binarySearch(arr, num, 0, n - 1);  // store result

  if (result == -1)
    printf("Element not found!\n");
  else
    printf("Element is found at index %d. \n", result);

  return 0;
}
