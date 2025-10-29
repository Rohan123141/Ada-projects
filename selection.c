#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// A utility function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to sort an array using selection sort
void selectionSort(int arr[], int n) {
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n - 1; i++) {
        // Find the minimum element in the unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

        // Swap the found minimum element with the first element
        // of the unsorted part.
        if (min_idx != i) {
            swap(&arr[min_idx], &arr[i]);
        }
    }
}

// Utility function to print an array
void printArray(int A[], int size) {
    // Print first 10 elements for brevity if size is large
    int limit = (size > 10) ? 10 : size;
    for (int i = 0; i < limit; i++)
        printf("%d ", A[i]);
    if (size > 10) printf("...");
    printf("\n");
}

int main() {
    int n;
    clock_t start, end;
    double cpu_time_used;

    // Seed the random number generator
    srand(time(NULL));

    printf("Enter the number of elements (n): ");
    scanf("%d", &n);

    // Dynamically allocate memory for the array
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Generate n random integers
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000; // Generate numbers between 0 and 9999
    }

    // Start the timer
    start = clock();

    // Perform selection sort
    selectionSort(arr, n);

    // Stop the timer
    end = clock();

    // Calculate the time taken in seconds
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nSorted array: ");
    printArray(arr, n);

    printf("\nTime taken to sort %d elements: %f seconds\n", n, cpu_time_used);

    // Free the dynamically allocated memory
    free(arr);

    return 0;
}