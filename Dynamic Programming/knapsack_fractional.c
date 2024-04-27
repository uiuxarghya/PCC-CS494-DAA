#include <stdio.h>

// Function to merge two subarrays of arr[]
// First subarray is arr[low..mid]
// Second subarray is arr[mid+1..high]
void merge(float arr[], int item[], int low, int mid, int high) {
  int i, t, j, k;
  i = t = low;
  j = mid + 1;
  float temp[high + 1];
  int index[high + 1];

  // Merge the two subarrays
  while (i <= mid && j <= high) {
    if (arr[i] >= arr[j]) {
      temp[t] = arr[i];
      index[t++] = item[i++];
    } else if (arr[j] > arr[i]) {
      temp[t] = arr[j];
      index[t++] = item[j++];
    }
  }

  // Copy the remaining elements of left subarray
  while (i <= mid) {
    temp[t] = arr[i];
    index[t++] = item[i++];
  }

  // Copy the remaining elements of right subarray
  while (j <= high) {
    temp[t] = arr[j];
    index[t++] = item[j++];
  }

  // Copy the merged elements back to original arrays
  for (k = low; k <= high; k++) {
    arr[k] = temp[k];
    item[k] = index[k];
  }
}

// Function to implement merge sort
void mergeSort(float arr[], int item[], int low, int high) {
  if (low < high) {
    int mid = (low + high) / 2;
    // Divide array into two halves and recursively sort them
    mergeSort(arr, item, low, mid);
    mergeSort(arr, item, mid + 1, high);
    // Merge the sorted halves
    merge(arr, item, low, mid, high);
  }
}

// Function to solve the knapsack problem
float knapsack(int item[], float val[], float w[], int n, float weight) {
  int i, index;
  float profit = 0, t;
  // Greedily select items based on their value/weight ratio
  for (i = 0; i < n; i++) {
    index = item[i] - 1;
    if (w[index] <= weight) {
      profit += val[index];
      weight -= w[index];
    } else {
      t = weight / w[index];
      profit += (t * val[index]);
      weight -= (t * w[index]);
    }
  }
  return profit;
}

// Function to input values and weights of items
void input(int n, float val[], float w[], int item[]) {
  printf("\nItem\t\tValue\tWeight\n");
  printf("------------------------------\n");
  for (int i = 0; i < n; i++) {
    printf("Item-%d :\t", i + 1);
    scanf("%f\t%f", &val[i], &w[i]);
    item[i] = i + 1;
  }
}

int main() {
  int i, n;
  float weight;
  printf("Enter the number of items : ");
  scanf("%d", &n);
  float val[n], w[n];
  int item[n];
  printf("Enter the value and weight of the items : \n");
  input(n, val, w, item);
  printf("\nEnter the weight of the knapsack : ");
  scanf("%f", &weight);

  // Calculate value/weight ratio for each item
  float fraction[n], temp[n];
  for (i = 0; i < n; i++) {
    fraction[i] = val[i] / w[i];
    temp[i] = fraction[i];
  }

  // Sort items based on value/weight ratio
  mergeSort(fraction, item, 0, n - 1);

  // Solve knapsack problem and print maximum profit
  float profit = knapsack(item, val, w, n, weight);
  printf("\nMaximum profit = %.2f\n\n", profit);

  return 0;
}
