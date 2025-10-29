#include <stdio.h>
#include <time.h>

#define MAX 1000

int memo[MAX];

// Recursive function with memoization (top-down DP)
int fibonacci(int n) {
    if (n == 0) {
        return 0; // Base case 0
    } else if (n == 1) {
        return 1; // Base case 1
    }

    if (memo[n] != -1) {
        return memo[n]; // Return cached result
    }

    // Calculate and cache result
    memo[n] = fibonacci(n - 1) + fibonacci(n - 2);
    return memo[n];
}

int main() {
    int n;

    printf("Enter the number of Fibonacci numbers to generate: ");
    scanf("%d", &n);

    // Initialize memo array with -1
    for (int i = 0; i < MAX; i++) {
        memo[i] = -1;
    }

    clock_t start = clock();

    printf("Fibonacci Series: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", fibonacci(i));
    }
    printf("\n");

    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_taken);

    return 0;
}
