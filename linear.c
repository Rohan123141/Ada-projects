#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target)
            return i;
    }
    return -1;
}

void generateRandomArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100000;
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
    generateRandomArray(arr, n);

    int target = arr[rand() % n];  // Random target from the array

    clock_t start = clock();
    for (int i = 0; i < 1000; i++) {
        linearSearch(arr, n, target);
    }
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC / 1000.0;
    printf("TIME TAKEN TO SEARCH %d ELEMENTS USING LINEAR SEARCH: %f seconds\n", n, time_taken);

    free(arr);
    return 0;
}
