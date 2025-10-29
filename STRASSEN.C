#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to allocate memory for matrix
int** allocateMatrix(int n) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }
    return matrix;
}

// Function to free matrix memory
void freeMatrix(int n, int** matrix) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Add matrices: C = A + B
void add(int n, int** A, int** B, int** C) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// Subtract matrices: C = A - B
void subtract(int n, int** A, int** B, int** C) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Strassen's multiply: C = A * B
void strassenMultiply(int n, int** A, int** B, int** C) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
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

    int **M1 = allocateMatrix(newSize);
    int **M2 = allocateMatrix(newSize);
    int **M3 = allocateMatrix(newSize);
    int **M4 = allocateMatrix(newSize);
    int **M5 = allocateMatrix(newSize);
    int **M6 = allocateMatrix(newSize);
    int **M7 = allocateMatrix(newSize);

    int **AResult = allocateMatrix(newSize);
    int **BResult = allocateMatrix(newSize);

    // Divide matrices into submatrices
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
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

    // M1 = (A11 + A22)*(B11 + B22)
    add(newSize, A11, A22, AResult);
    add(newSize, B11, B22, BResult);
    strassenMultiply(newSize, AResult, BResult, M1);

    // M2 = (A21 + A22)*B11
    add(newSize, A21, A22, AResult);
    strassenMultiply(newSize, AResult, B11, M2);

    // M3 = A11*(B12 - B22)
    subtract(newSize, B12, B22, BResult);
    strassenMultiply(newSize, A11, BResult, M3);

    // M4 = A22*(B21 - B11)
    subtract(newSize, B21, B11, BResult);
    strassenMultiply(newSize, A22, BResult, M4);

    // M5 = (A11 + A12)*B22
    add(newSize, A11, A12, AResult);
    strassenMultiply(newSize, AResult, B22, M5);

    // M6 = (A21 - A11)*(B11 + B12)
    subtract(newSize, A21, A11, AResult);
    add(newSize, B11, B12, BResult);
    strassenMultiply(newSize, AResult, BResult, M6);

    // M7 = (A12 - A22)*(B21 + B22)
    subtract(newSize, A12, A22, AResult);
    add(newSize, B21, B22, BResult);
    strassenMultiply(newSize, AResult, BResult, M7);

    // Combine results into C submatrices
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            C[i][j + newSize] = M3[i][j] + M5[i][j];
            C[i + newSize][j] = M2[i][j] + M4[i][j];
            C[i + newSize][j + newSize] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
        }
    }

    // Free allocated memory
    freeMatrix(newSize, A11); freeMatrix(newSize, A12); freeMatrix(newSize, A21); freeMatrix(newSize, A22);
    freeMatrix(newSize, B11); freeMatrix(newSize, B12); freeMatrix(newSize, B21); freeMatrix(newSize, B22);
    freeMatrix(newSize, M1); freeMatrix(newSize, M2); freeMatrix(newSize, M3); freeMatrix(newSize, M4);
    freeMatrix(newSize, M5); freeMatrix(newSize, M6); freeMatrix(newSize, M7);
    freeMatrix(newSize, AResult); freeMatrix(newSize, BResult);
}

int main() {
    int sizes[] = {128, 256, 512}; // Powers of 2 matrix sizes
    for(int idx = 0; idx < 3; idx++) {
        int n = sizes[idx];

        int **A = allocateMatrix(n);
        int **B = allocateMatrix(n);
        int **C = allocateMatrix(n);

        // Fill matrices A and B with random values
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                A[i][j] = rand() % 10;
                B[i][j] = rand() % 10;
                C[i][j] = 0;
            }

        clock_t start = clock();
        strassenMultiply(n, A, B, C);
        clock_t end = clock();

        printf("Strassen multiplication execution time for %d x %d: %lf seconds\n",
               n, n, (double)(end - start) / CLOCKS_PER_SEC);

        // Free allocated matrices
        freeMatrix(n, A);
        freeMatrix(n, B);
        freeMatrix(n, C);
    }
    return 0;
}
