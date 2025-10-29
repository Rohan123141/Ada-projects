#include <stdio.h>
#include <time.h>

int fibonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    int fib[n+1];
    fib[0] = 0;
    fib[1] = 1;

    for (int i = 2; i <= n; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }

    return fib[n];
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
