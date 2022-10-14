#include <stdio.h>

void merge_sort();
int *swap(int a, int b); // int *swap(int *nums);
void print_nums(int nums[], int len);

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r) {
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;
  /* create temp arrays */
  int L[n1], R[n2];
  /* Copy data to temp arrays L[] and R[] */
  for (i = 0; i < n1; i++)
    L[i] = arr[l + i];
  for (j = 0; j < n2; j++)
    R[j] = arr[m + 1 + j];
  /* Merge the temp arrays back into arr[l..r]*/
  i = 0; // Initial index of first subarray
  j = 0; // Initial index of second subarray
  k = l; // Initial index of merged subarray
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }
  /* Copy the remaining elements of L[], if there
  are any */
  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }
  /* Copy the remaining elements of R[], if there
  are any */
  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }
}

/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r) {
  if (l < r) {
    // Same as (l+r)/2, but avoids overflow for large l and h
    int m = l + (r - l) / 2;
    // Sort first and second halves
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
  }
}

/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(int A[], int size) {
  int i;
  for (i = 0; i < size; i++)
    printf("%d ", A[i]);
  printf("\n");
}

/* Driver code */
int main() {
  int arr[] = {12, 11, 13, 5, 6, 7};
  int arr_size = sizeof(arr) / sizeof(arr[0]);
  printf("Given array is \n");
  printArray(arr, arr_size);
  mergeSort(arr, 0, arr_size - 1);
  printf("\nSorted array is \n");
  printArray(arr, arr_size);
  return 0;
}

// They sort a smaller piece of a problem
// when recursive func calls itself.
//
// # Pseudocode:
//
// Sort left half of numbers.
// Sort right half of numbers.
// Merge sorted halves.
int mainRun(int argc, char *argv[]) {
  merge_sort();
  return 0;
}
/* https://cs50.harvard.edu/x/2022/psets/3/plurality/
    step 1: start
    step 2: declare array and left, right, mid variable
    step 3: perform merge function.
        if left > right
            return
        mid= (left+right)/2
        mergesort(array, left, mid)
        mergesort(array, mid+1, right)
        merge(array, left, mid, right)
    step 4: Stop */

/* Follow the steps below the solve the problem:
    MergeSort(arr[], l,  r)
    If r > l
    Find the middle point to divide the array into two halves:
    middle m = l + (r – l)/2
    Call mergeSort for first half:
    Call mergeSort(arr, l, m)
    Call mergeSort for second half:
    Call mergeSort(arr, m + 1, r)
    Merge the two halves sorted in steps 2 and 3:
    Call merge(arr, l, m, r) */

void merge_sort() {
  int nums[] = {4, 2, 5, 7, 0, 1, 3, 6};
  int len = sizeof(nums) / sizeof(nums[0]);
  if (len <= 1) {
    return;
  } else {
    print_nums(nums, len);
    int *cache = swap(nums[0], nums[1]);
    nums[0] = cache[0];
    nums[1] = cache[1];
    printf("%i %i\n", cache[0], cache[1]);
  }
  print_nums(nums, len);
}

int *swap(int a, int b) {
  if (a > b) {
    int *n[] = {&b, &a};
    return *n;
  } else {
    int *n[] = {&a, &b};
    return *n;
  }
}

// Print nums[].
void print_nums(int nums[], int len) {
  for (int i = 0; i < len; i++) {
    printf("%i ", nums[i]);
  }
  printf("\n");
}

void archive() {
  int nums[] = {2, 4, 5, 7, 0, 1, 3, 6};
  int len = sizeof(nums) / sizeof(nums[0]);
  for (int i = 0; i < len; i++) {
    printf("%i ", nums[i]);
  }
  int left = 0, right = nums[len - 1];
  while (left != right) {
    int mid = (left + right) / 2;
    printf("\n%i,%i,%i\n", left, mid, right);
    int n = nums[mid];
    if (n < nums[left]) {
      nums[mid] = nums[left];
      nums[left] = n;
      left++;
    } else {
      // left--;
    }
    if (n > nums[right]) {
      nums[mid] = nums[right];
      nums[right] = n;
      right--;
    }
    printf("%d\n", nums[mid]);
    for (int i = 0; i < len; i++) {
      printf("%i ", nums[i]);
    }
    printf("\nover: %i,%i\n", left, right);
  }
}
