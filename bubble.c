#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> // For bool type

// A utility function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// An optimized function to sort an array using bubble sort
void bubbleSort(int arr[], int n) {
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }

        // If no two elements were swapped by inner loop, then break
        if (swapped == false) {
            break;
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

    // Perform bubble sort
    bubbleSort(arr, n);

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