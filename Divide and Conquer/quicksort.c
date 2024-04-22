#include <stdio.h>
#include <stdlib.h>

int partition(int arr[], int low, int high) {
  int pivot = arr[high];
  int i = (low - 1);

  for (int j = low; j <= high; j++) {
    if (arr[j] < pivot) {
      i++;
      int temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
    }
  }
  int temp = arr[i + 1];
  arr[i + 1] = arr[high];
  arr[high] = temp;
  return (i + 1);
}

void quickSort(int arr[], int low, int high) {
  if (low < high) {

    int pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}

void printArray(int arr[], int size) {
  int i;
  for (i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int main() {
  int n, i;
  printf("Enter the array size: ");
  scanf("%d", &n);

  printf("\n");

  int arr[n];

  for (i = 0; i < n; i++) {
    printf("Enter the value of arr[%d]: ", i);
    scanf("%d", &arr[i]);
  }

  printf("\nGiven Array: ");
  printArray(arr, n);

  quickSort(arr, 0, n - 1);

  printf("\nSorted Array: ");
  printArray(arr, n);

  return 0;
}
