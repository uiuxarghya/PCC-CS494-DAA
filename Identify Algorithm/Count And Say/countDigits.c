#include <stdio.h>

// Function to count the number of occurrences of 'index' in the array 'arr'
int repeat(int arr[], int index) {
  int count = 0;
  int i;
  
  // Iterate through the array to count occurrences of 'index'
  for(i = 0; i < 10; i++) {
    if(arr[i] == index) {
      count++;
    }
  }
  
  return count;
}

void main() {
  // Initialize the array with one occurrence of 9 and nine occurrences of 0
  int arr[] = {9, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  
  int temp, i;
  int hasChanges = 1; // Flag to track changes in the array
  
  // Loop until no changes are made to the array
  while(hasChanges == 1) {
    hasChanges = 0; // Reset the flag before each iteration
    // Iterate through the array
    for(i = 0; i < 10; i++) {
      // Count the occurrences of the current index 'i' in the array
      temp = repeat(arr, i);
      // If the count is different from the value at index 'i', update the value
      if(arr[i] != temp) {
        hasChanges = 1; // Set the flag to indicate changes are made
        arr[i] = temp; // Update the value at index 'i'
      }
    }
  }
  
  // Print the resulting array
  printf("Result : ");
  for(i = 0; i < 10; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}
