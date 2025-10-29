#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure to represent an item
typedef struct {
    int value;
    int weight;
} Item;

// Comparator for sorting items by value/weight ratio
int compare(const void *a, const void *b) {
    double r1 = (double)((Item *)a)->value / ((Item *)a)->weight;
    double r2 = (double)((Item *)b)->value / ((Item *)b)->weight;
    return (r2 > r1) - (r2 < r1);  // descending order
}

// Function for Fractional Knapsack
double fractionalKnapsack(Item arr[], int n, int W) {
    qsort(arr, n, sizeof(Item), compare);
    double totalValue = 0.0;

    for (int i = 0; i < n; i++) {
        if (arr[i].weight <= W) {
            totalValue += arr[i].value;
            W -= arr[i].weight;
        } else {
            totalValue += arr[i].value * ((double)W / arr[i].weight);
            break;
        }
    }
    return totalValue;
}

int main() {
    int n, W;
    printf("Enter number of items: ");
    scanf("%d", &n);
    printf("Enter Knapsack Capacity: ");
    scanf("%d", &W);

    if (n < 5000) {
        printf("Please enter a value >= 5000 for better time comparison.\n");
    }

    Item *arr = (Item *)malloc(n * sizeof(Item));
    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        arr[i].value = rand() % 100 + 1;
        arr[i].weight = rand() % 50 + 1;
    }

    // Measure average execution time
    int iterations = 1000;
    clock_t start = clock();
    for (int i = 0; i < iterations; i++) {
        fractionalKnapsack(arr, n, W);
    }
    clock_t end = clock();

    double avg_time = ((double)(end - start)) / CLOCKS_PER_SEC / iterations;

    printf("\n===== FRACTIONAL KNAPSACK (GREEDY) =====\n");
    printf("Average Execution Time: %f seconds\n", avg_time);
    printf("Time Complexity: O(n log n)\n");
    printf("Space Complexity: O(1)\n");

    free(arr);
    return 0;
}