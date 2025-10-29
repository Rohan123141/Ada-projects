#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to allocate dynamic matrix
int** allocateMatrix(int n) {
    int **matrix = (int **)malloc(n * sizeof(int *));
    for(int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }
    return matrix;
}

// Function to free dynamic matrix
void freeMatrix(int n, int **matrix) {
    for(int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to add two matrices: C = A + B
void add(int n, int **A, int **B, int **C) {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// Function to subtract matrix B from A: C = A - B
void subtract(int n, int **A, int **B, int **C) {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Recursive divide and conquer multiplication: C = A * B
void multiply(int n, int **A, int **B, int **C) {
    if(n == 1) {
        C[0][0] += A[0][0] * B[0][0];
        return;
    }

    int newSize = n / 2;

    // Allocate submatrices
    int **A11 = allocateMatrix(newSize);
    int **A12 = allocateMatrix(newSize);
    int **A21 = allocateMatrix(newSize);
    int **A22 = allocateMatrix(newSize);
    int **B11 = allocateMatrix(newSize);
    int **B12 = allocateMatrix(newSize);
    int **B21 = allocateMatrix(newSize);
    int **B22 = allocateMatrix(newSize);
    int **C11 = allocateMatrix(newSize);
    int **C12 = allocateMatrix(newSize);
    int **C21 = allocateMatrix(newSize);
    int **C22 = allocateMatrix(newSize);
    int **temp1 = allocateMatrix(newSize);
    int **temp2 = allocateMatrix(newSize);

    // Initialize C submatrices to 0
    for(int i=0; i<newSize; i++)
        for(int j=0; j<newSize; j++) {
            C11[i][j] = 0; C12[i][j] = 0; C21[i][j] = 0; C22[i][j] = 0;
            temp1[i][j] = 0; temp2[i][j] = 0;
        }

    // Divide input matrices into 4 submatrices
    for(int i=0; i<newSize; i++) {
        for(int j=0; j<newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Compute C11 = A11*B11 + A12*B21
    multiply(newSize, A11, B11, C11);
    multiply(newSize, A12, B21, C11);

    // Compute C12 = A11*B12 + A12*B22
    multiply(newSize, A11, B12, C12);
    multiply(newSize, A12, B22, C12);

    // Compute C21 = A21*B11 + A22*B21
    multiply(newSize, A21, B11, C21);
    multiply(newSize, A22, B21, C21);

    // Compute C22 = A21*B12 + A22*B22
    multiply(newSize, A21, B12, C22);
    multiply(newSize, A22, B22, C22);

    // Combine results into matrix C
    for(int i=0; i<newSize; i++) {
        for(int j=0; j<newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    // Free all allocated matrices
    freeMatrix(newSize, A11); freeMatrix(newSize, A12);
    freeMatrix(newSize, A21); freeMatrix(newSize, A22);
    freeMatrix(newSize, B11); freeMatrix(newSize, B12);
    freeMatrix(newSize, B21); freeMatrix(newSize, B22);
    freeMatrix(newSize, C11); freeMatrix(newSize, C12);
    freeMatrix(newSize, C21); freeMatrix(newSize, C22);
    freeMatrix(newSize, temp1); freeMatrix(newSize, temp2);
}

int main() {
    int sizes[] = {100, 500, 1000};  // Must be powers of 2
    for(int idx = 0; idx < 3; idx++) {
        int n = sizes[idx];

        // Allocate matrices
        int **A = allocateMatrix(n);
        int **B = allocateMatrix(n);
        int **C = allocateMatrix(n);

        // Fill A and B with random values
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++) {
                A[i][j] = rand() % 10;
                B[i][j] = rand() % 10;
                C[i][j] = 0;
            }

        clock_t start = clock();
        multiply(n, A, B, C);
        clock_t end = clock();

        printf("Execution time for %d x %d: %lf seconds\n", n, n,
               (double)(end - start) / CLOCKS_PER_SEC);

        // Free matrices
        freeMatrix(n, A);
        freeMatrix(n, B);
        freeMatrix(n, C);
    }

    return 0;
}
