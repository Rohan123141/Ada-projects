#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to multiply two matrices of size n x n
void multiply(int n) {
    int i, j, k;
    // Dynamic allocation
    int **a = (int **)malloc(n*sizeof(int *));
    int **b = (int **)malloc(n*sizeof(int *));
    int **result = (int **)malloc(n*sizeof(int *));
    for(i = 0; i < n; i++) {
        a[i] = (int *)malloc(n*sizeof(int));
        b[i] = (int *)malloc(n*sizeof(int));
        result[i] = (int *)malloc(n*sizeof(int));
    }
    // Initialize matrices with random values
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++) {
            a[i][j] = rand() % 10;
            b[i][j] = rand() % 10;
            result[i][j] = 0;
        }
    // Measure multiplication time
    clock_t start = clock();
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            for(k = 0; k < n; k++)
                result[i][j] += a[i][k] * b[k][j];
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Execution time for %d x %d: %f seconds\n", n, n, time_spent);
    // Free memory
    for(i = 0; i < n; i++) {
        free(a[i]);
        free(b[i]);
        free(result[i]);
    }
    free(a); free(b); free(result);
}

int main() {
    int sizes[] = {100, 500, 1000}; // Matrix sizes to compare
    for(int i = 0; i < 3; i++)
        multiply(sizes[i]);
    return 0;
}
