#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to sort an array using insertion sort
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
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

    // printf("Unsorted array: ");
    // printArray(arr, n);

    // Start the timer
    start = clock();

    // Perform insertion sort
    insertionSort(arr, n);

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