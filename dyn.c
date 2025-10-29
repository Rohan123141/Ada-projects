#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure to represent an item
typedef struct {
    int value;
    int weight;
} Item;

// Function for 0/1 Knapsack using Dynamic Programming
int knapsackDP(Item arr[], int n, int W) {
    int **K = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++)
        K[i] = (int *)malloc((W + 1) * sizeof(int));

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (arr[i - 1].weight <= w)
                K[i][w] = (arr[i - 1].value + K[i - 1][w - arr[i - 1].weight] > K[i - 1][w])
                              ? arr[i - 1].value + K[i - 1][w - arr[i - 1].weight]
                              : K[i - 1][w];
            else
                K[i][w] = K[i - 1][w];
        }
    }

    int result = K[n][W];

    // Free allocated memory
    for (int i = 0; i <= n; i++)
        free(K[i]);
    free(K);

    return result;
}

int main() {
    int n, W;
    printf("Enter number of items: ");
    scanf("%d", &n);
    printf("Enter Knapsack Capacity: ");
    scanf("%d", &W);

    if (n < 50) {
        printf("Please enter a value >= 50 for noticeable timing.\n");
    }

    Item *arr = (Item *)malloc(n * sizeof(Item));
    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        arr[i].value = rand() % 100 + 1;
        arr[i].weight = rand() % (W / 2) + 1;
    }

    // Measure average execution time
    int iterations = 10;  // DP is slower, so fewer iterations
    clock_t start = clock();
    for (int i = 0; i < iterations; i++) {
        knapsackDP(arr, n, W);
    }
    clock_t end = clock();

    double avg_time = ((double)(end - start)) / CLOCKS_PER_SEC / iterations;

    printf("\n===== 0/1 KNAPSACK (DYNAMIC PROGRAMMING) =====\n");
    printf("Average Execution Time: %f seconds\n", avg_time);
    printf("Time Complexity: O(n * W)\n");
    printf("Space Complexity: O(n * W)\n");

    free(arr);
    return 0;
}