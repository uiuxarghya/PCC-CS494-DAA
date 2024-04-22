#include <stdio.h>

void merge(float arr[], int item[], int low, int mid, int high) {
  int i,t,j,k;
  i = t = low;
  j = mid+1;
  float temp[high+1];
  int index[high+1];
  while(i<=mid && j<=high) {
    if(arr[i] >= arr[j]) {
      temp[t] = arr[i];
      index[t++] = item[i++];
    } else if(arr[j] > arr[i]) {
      temp[t] = arr[j];
      index[t++] = item[j++];
    }
  }
  while(i <= mid) {
    temp[t] = arr[i];
    index[t++] = item[i++];
  }
  while(j <= high) {
    temp[t] = arr[j];
    index[t++] = item[j++];
  }
  for(k=low; k<=high; k++) {
    arr[k] = temp[k];
    item[k] = index[k];
  }
}

void mergeSort(float arr[], int item[], int low, int high) {
  if(low < high) {
    int mid = (low+high) / 2;
    mergeSort(arr,item,low,mid);
    mergeSort(arr,item,mid+1,high);
    merge(arr,item,low,mid,high);
  }
}

float knapsack(int item[],float val[],float w[],int n,float weight) {
  int i,index;
  float profit = 0,t;
  for(i=0; i<n; i++) {
    index = item[i] - 1;
    if(w[index] <= weight) {
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

void input(int n, float val[], float w[],int item[]) {
  printf("\nItem\t\tValue\tWeight\n");
  printf("------------------------------\n");
  for(int i=0; i<n; i++) {
    printf("Item-%d :\t",i+1);
    scanf("%f\t%f",&val[i],&w[i]);
    item[i] = i+1;
  }
}

void main() {
  int i,n;
  float weight;
  printf("Enter the number of items : ");
  scanf("%d",&n);
  float val[n], w[n];
  int item[n];
  printf("Enter the value and weight of the items : \n");
  input(n,val,w,item);
  printf("\nEnter the weight of the knapsack : ");
  scanf("%f",&weight);

  float fraction[n],temp[n];
  for(i=0; i<n; i++) {
    fraction[i] = val[i] / w[i];
    temp[i] = fraction[i];
  }

  mergeSort(fraction,item,0,n-1);

  float profit = knapsack(item,val,w,n,weight);

  printf("\nMaximum profit = %.2f\n\n",profit);
}
