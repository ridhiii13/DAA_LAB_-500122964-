#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 2  // Define the matrix size as 2x2 or higher powers of 2 for Strassen's method

// Function prototypes
void traditionalMultiplication(int A[SIZE][SIZE], int B[SIZE][SIZE], int C[SIZE][SIZE]);
void strassenMultiplication(int A[SIZE][SIZE], int B[SIZE][SIZE], int C[SIZE][SIZE]);
void addMatrix(int A[SIZE][SIZE], int B[SIZE][SIZE], int C[SIZE][SIZE]);
void subtractMatrix(int A[SIZE][SIZE], int B[SIZE][SIZE], int C[SIZE][SIZE]);
void printMatrix(int matrix[SIZE][SIZE]);

int main() {
    int A[SIZE][SIZE] = {{1, 2}, {3, 4}};
    int B[SIZE][SIZE] = {{5, 6}, {7, 8}};
    int C1[SIZE][SIZE], C2[SIZE][SIZE];  // Result matrices

    clock_t start, end;
    double time_taken;

    // Traditional matrix multiplication
    start = clock();
    traditionalMultiplication(A, B, C1);
    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Traditional Multiplication Result:\n");
    printMatrix(C1);
    printf("Time taken by Traditional Multiplication: %.6f seconds\n", time_taken);

    // Strassen's matrix multiplication
    start = clock();
    strassenMultiplication(A, B, C2);
    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nStrassen's Multiplication Result:\n");
    printMatrix(C2);
    printf("Time taken by Strassen's Multiplication: %.6f seconds\n", time_taken);

    return 0;
}

// Function for traditional matrix multiplication
void traditionalMultiplication(int A[SIZE][SIZE], int B[SIZE][SIZE], int C[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            C[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Function for Strassen's matrix multiplication
void strassenMultiplication(int A[SIZE][SIZE], int B[SIZE][SIZE], int C[SIZE][SIZE]) {
    if (SIZE == 2) {
        int M1 = (A[0][0] + A[1][1]) * (B[0][0] + B[1][1]);
        int M2 = (A[1][0] + A[1][1]) * B[0][0];
        int M3 = A[0][0] * (B[0][1] - B[1][1]);
        int M4 = A[1][1] * (B[1][0] - B[0][0]);
        int M5 = (A[0][0] + A[0][1]) * B[1][1];
        int M6 = (A[1][0] - A[0][0]) * (B[0][0] + B[0][1]);
        int M7 = (A[0][1] - A[1][1]) * (B[1][0] + B[1][1]);

        C[0][0] = M1 + M4 - M5 + M7;
        C[0][1] = M3 + M5;
        C[1][0] = M2 + M4;
        C[1][1] = M1 - M2 + M3 + M6;
    } else {
        printf("Strassen's method is currently implemented only for 2x2 matrices.\n");
    }
}

// Helper function to add two matrices
void addMatrix(int A[SIZE][SIZE], int B[SIZE][SIZE], int C[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Helper function to subtract two matrices
void subtractMatrix(int A[SIZE][SIZE], int B[SIZE][SIZE], int C[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Function to print a matrix
void printMatrix(int matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}