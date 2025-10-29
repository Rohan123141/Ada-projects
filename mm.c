#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ----------------------------
// Utility Functions
// ----------------------------
int** allocate_matrix(int n) {
    int** M = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        M[i] = (int*)calloc(n, sizeof(int));
    return M;
}

void free_matrix(int** M, int n) {
    for (int i = 0; i < n; i++) free(M[i]);
    free(M);
}

void fill_matrix(int** M, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            M[i][j] = rand() % 10;
}

void copy_block(int** src, int** dest, int row, int col, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dest[i][j] = src[i+row][j+col];
}

void place_block(int** src, int** dest, int row, int col, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dest[i+row][j+col] = src[i][j];
}

void add_matrix(int** A, int** B, int** C, int n) {
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            C[i][j] = A[i][j] + B[i][j];
}

void sub_matrix(int** A, int** B, int** C, int n) {
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            C[i][j] = A[i][j] - B[i][j];
}

// ----------------------------
// Iterative Multiplication
// ----------------------------
void iterative_mult(int** A, int** B, int** C, int n) {
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++) {
            C[i][j] = 0;
            for (int k=0;k<n;k++)
                C[i][j] += A[i][k]*B[k][j];
        }
}

// ----------------------------
// Divide and Conquer Multiplication
// ----------------------------
void divide_conquer_mult(int** A, int** B, int** C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0]*B[0][0];
        return;
    }

    int mid = n/2;

    int** A11 = allocate_matrix(mid); int** A12 = allocate_matrix(mid);
    int** A21 = allocate_matrix(mid); int** A22 = allocate_matrix(mid);
    int** B11 = allocate_matrix(mid); int** B12 = allocate_matrix(mid);
    int** B21 = allocate_matrix(mid); int** B22 = allocate_matrix(mid);

    copy_block(A, A11, 0, 0, mid);   copy_block(A, A12, 0, mid, mid);
    copy_block(A, A21, mid, 0, mid); copy_block(A, A22, mid, mid, mid);

    copy_block(B, B11, 0, 0, mid);   copy_block(B, B12, 0, mid, mid);
    copy_block(B, B21, mid, 0, mid); copy_block(B, B22, mid, mid, mid);

    int** C11 = allocate_matrix(mid); int** C12 = allocate_matrix(mid);
    int** C21 = allocate_matrix(mid); int** C22 = allocate_matrix(mid);

    int** T1 = allocate_matrix(mid); int** T2 = allocate_matrix(mid);

    divide_conquer_mult(A11, B11, T1, mid);
    divide_conquer_mult(A12, B21, T2, mid);
    add_matrix(T1, T2, C11, mid);

    divide_conquer_mult(A11, B12, T1, mid);
    divide_conquer_mult(A12, B22, T2, mid);
    add_matrix(T1, T2, C12, mid);

    divide_conquer_mult(A21, B11, T1, mid);
    divide_conquer_mult(A22, B21, T2, mid);
    add_matrix(T1, T2, C21, mid);

    divide_conquer_mult(A21, B12, T1, mid);
    divide_conquer_mult(A22, B22, T2, mid);
    add_matrix(T1, T2, C22, mid);

    place_block(C11, C, 0, 0, mid);
    place_block(C12, C, 0, mid, mid);
    place_block(C21, C, mid, 0, mid);
    place_block(C22, C, mid, mid, mid);

    free_matrix(A11, mid); free_matrix(A12, mid); free_matrix(A21, mid); free_matrix(A22, mid);
    free_matrix(B11, mid); free_matrix(B12, mid); free_matrix(B21, mid); free_matrix(B22, mid);
    free_matrix(C11, mid); free_matrix(C12, mid); free_matrix(C21, mid); free_matrix(C22, mid);
    free_matrix(T1, mid);  free_matrix(T2, mid);
}

// ----------------------------
// Strassen Multiplication
// ----------------------------
void strassen_mult(int** A, int** B, int** C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0]*B[0][0];
        return;
    }

    int mid = n/2;

    int** A11 = allocate_matrix(mid); int** A12 = allocate_matrix(mid);
    int** A21 = allocate_matrix(mid); int** A22 = allocate_matrix(mid);
    int** B11 = allocate_matrix(mid); int** B12 = allocate_matrix(mid);
    int** B21 = allocate_matrix(mid); int** B22 = allocate_matrix(mid);

    copy_block(A, A11, 0, 0, mid);   copy_block(A, A12, 0, mid, mid);
    copy_block(A, A21, mid, 0, mid); copy_block(A, A22, mid, mid, mid);

    copy_block(B, B11, 0, 0, mid);   copy_block(B, B12, 0, mid, mid);
    copy_block(B, B21, mid, 0, mid); copy_block(B, B22, mid, mid, mid);

    int** M1 = allocate_matrix(mid); int** M2 = allocate_matrix(mid);
    int** M3 = allocate_matrix(mid); int** M4 = allocate_matrix(mid);
    int** M5 = allocate_matrix(mid); int** M6 = allocate_matrix(mid);
    int** M7 = allocate_matrix(mid);

    int** T1 = allocate_matrix(mid); int** T2 = allocate_matrix(mid);

    add_matrix(A11, A22, T1, mid);
    add_matrix(B11, B22, T2, mid);
    strassen_mult(T1, T2, M1, mid);

    add_matrix(A21, A22, T1, mid);
    strassen_mult(T1, B11, M2, mid);

    sub_matrix(B12, B22, T1, mid);
    strassen_mult(A11, T1, M3, mid);

    sub_matrix(B21, B11, T1, mid);
    strassen_mult(A22, T1, M4, mid);

    add_matrix(A11, A12, T1, mid);
    strassen_mult(T1, B22, M5, mid);

    sub_matrix(A21, A11, T1, mid);
    add_matrix(B11, B12, T2, mid);
    strassen_mult(T1, T2, M6, mid);

    sub_matrix(A12, A22, T1, mid);
    add_matrix(B21, B22, T2, mid);
    strassen_mult(T1, T2, M7, mid);

    int** C11 = allocate_matrix(mid); int** C12 = allocate_matrix(mid);
    int** C21 = allocate_matrix(mid); int** C22 = allocate_matrix(mid);

    add_matrix(M1, M4, T1, mid);
    sub_matrix(T1, M5, T2, mid);
    add_matrix(T2, M7, C11, mid);

    add_matrix(M3, M5, C12, mid);
    add_matrix(M2, M4, C21, mid);

    sub_matrix(M1, M2, T1, mid);
    add_matrix(T1, M3, T2, mid);
    add_matrix(T2, M6, C22, mid);

    place_block(C11, C, 0, 0, mid);
    place_block(C12, C, 0, mid, mid);
    place_block(C21, C, mid, 0, mid);
    place_block(C22, C, mid, mid, mid);

    free_matrix(A11, mid); free_matrix(A12, mid); free_matrix(A21, mid); free_matrix(A22, mid);
    free_matrix(B11, mid); free_matrix(B12, mid); free_matrix(B21, mid); free_matrix(B22, mid);
    free_matrix(M1, mid); free_matrix(M2, mid); free_matrix(M3, mid);
    free_matrix(M4, mid); free_matrix(M5, mid); free_matrix(M6, mid); free_matrix(M7, mid);
    free_matrix(T1, mid); free_matrix(T2, mid);
    free_matrix(C11, mid); free_matrix(C12, mid); free_matrix(C21, mid); free_matrix(C22, mid);
}

// ----------------------------
// Main
// ----------------------------
int main() {
    srand(time(NULL));

    int n;
    printf("Enter size of matrix (must be power of 2): ");
    scanf("%d", &n);

    // Check if n is power of 2
    if (n <= 0 || (n & (n-1)) != 0) {
        printf("Error: Size must be a power of 2 (e.g., 2, 4, 8, 16,...)\n");
        return 1;
    }

    int** A = allocate_matrix(n);
    int** B = allocate_matrix(n);
    int** C = allocate_matrix(n);

    fill_matrix(A, n);
    fill_matrix(B, n);

    clock_t start, end;

    start = clock();
    iterative_mult(A, B, C, n);
    end = clock();
    double t_iter = (double)(end-start)/CLOCKS_PER_SEC;

    start = clock();
    divide_conquer_mult(A, B, C, n);
    end = clock();
    double t_div = (double)(end-start)/CLOCKS_PER_SEC;

    start = clock();
    strassen_mult(A, B, C, n);
    end = clock();
    double t_strassen = (double)(end-start)/CLOCKS_PER_SEC;

    printf("Execution Times (n=%d):\n", n);
    printf("Iterative       : %.5f s\n", t_iter);
    printf("Divide-Conquer  : %.5f s\n", t_div);
    printf("Strassen        : %.5f s\n", t_strassen);

    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(C, n);

    return 0;
}
