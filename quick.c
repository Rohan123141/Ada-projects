#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // pivot
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

void generateRandomArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 100000;
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    if (n < 5000) {
        printf("Please enter a value greater than 5000\n");
        return 1;
    }
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    generateRandomArray(arr, n);

    clock_t start = clock();
    for (int i = 0; i < 500; i++)
        quicksort(arr, 0, n - 1);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC / 500.0;

    printf("TIME TAKEN TO SORT %d ELEMENTS: %f seconds\n", n, time_taken);

    free(arr);
    return 0;
}
