#include <stdio.h>
#include <time.h>

// Recursive function to calculate nth Fibonacci number
int fibonacci(int n) {
    if (n == 0) {
        return 0;             // Base case 0
    } else if (n == 1) {
        return 1;             // Base case 1
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2); // Recursive call
    }
}

int main() {
    int n;

    printf("Enter the number of Fibonacci numbers to generate: ");
    scanf("%d", &n);

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
