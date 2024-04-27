#include <stdio.h>

// Function to print an array
void print_array(int arr[], int n) {
  int i;
  for(i = 0; i < n; i++) {
    printf("%d\t", arr[i]);
  }
  printf("\n");
}

// Merge two subarrays of finish[] array
void merge(int job[], int start[], int finish[], int low, int mid, int high) {
  int i = low;
  int j = mid + 1;
  int k, t = low;
  int temp[high + 1], task[high + 1], s[high + 1];
  
  // Merge the two subarrays
  while(i <= mid && j <= high) {
    if(finish[i] < finish[j]) {
      temp[t] = finish[i];
      task[t] = job[i];
      s[t++] = start[i++];
    } else {
      temp[t] = finish[j];
      task[t] = job[j];
      s[t++] = start[j++];
    }
  }
  
  // Copy the remaining elements of left subarray
  while(i <= mid) {
    temp[t] = finish[i];
    task[t] = job[i];
    s[t++] = start[i++];
  }
  
  // Copy the remaining elements of right subarray
  while(j <= high) {
    temp[t] = finish[j];
    task[t] = job[j];
    s[t++] = start[j++];
  }
  
  // Copy the merged elements back to original arrays
  for(k = low; k <= high; k++) {
    finish[k] = temp[k];
    job[k] = task[k];
    start[k] = s[k];
  }
}

// Main function for merge sort
void mergeSort(int job[], int start[], int finish[], int low, int high) {
  if(low < high) {
    int mid = (low + high) / 2;
    // Sort the first and second halves
    mergeSort(job, start, finish, low, mid);
    mergeSort(job, start, finish, mid + 1, high);
    // Merge the sorted halves
    merge(job, start, finish, low, mid, high);
  }
}

// Function to schedule the jobs
void schedule(int job[], int start[], int finish[], int n) {
  int assigned[n], k = 0, i, j;
  mergeSort(job, start, finish, 0, n - 1);

  j = 0;
  assigned[k++] = job[j];
  
  // Select jobs that can be scheduled
  for(i = 1; i < n; i++) {
    if(start[i] >= finish[j]) {
      assigned[k++] = job[i];
      j = i;
    }
  }
  
  printf("\nScheduled jobs are :\t");
  print_array(assigned, k);
}

// Function to input job data
void input(int job[], int start[], int finish[], int n) {
  int i;
  printf("\nEnter the data : \n");
  printf("Jobs\tStart\tFinish\n");
  printf("---------------------------------------\n");
  for(i = 0; i < n; i++) {
    printf("Job-%d : ", i + 1);
    job[i] = i + 1;
    scanf("%d\t%d", &start[i], &finish[i]);
  }
}

// Main function
void main() {
  int n, i;
  printf("Enter the number of tasks : ");
  scanf("%d", &n);
  int job[n], start[n], finish[n];
  input(job, start, finish, n);

  schedule(job, start, finish, n);
}
