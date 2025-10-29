#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int binarySearch(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

void generateSortedArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i * 2; // Sorted array of even numbers
    }
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
    generateSortedArray(arr, n);
    int target = arr[rand() % n];  // Random target from array

    clock_t start = clock();
    for (int i = 0; i < 1000; i++) {
        binarySearch(arr, n, target);
    }
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC / 1000.0;
    printf("TIME TAKEN TO SEARCH %d ELEMENTS USING BINARY SEARCH: %f seconds\n", n, time_taken);

    free(arr);
    return 0;
}