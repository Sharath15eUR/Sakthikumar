#include <stdio.h>
#include <stdbool.h>

bool searchMatrix(int matrix[][100], int n, int key) {
    int row = 0, col = n - 1;  // Start from top-right

    while (row < n && col >= 0) {
        if (matrix[row][col] == key)
            return true;
        else if (matrix[row][col] > key)
            col--;  // Move left
        else
            row++;  // Move down
    }
    return false;
}

void printMatrix(int matrix[][100], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n, key;
    int matrix[100][100];

    printf("Enter the size of the matrix (n x n): ");
    scanf("%d", &n);

    printf("Enter the elements: \n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &matrix[i][j]);

    printf("\nMatrix:\n");
    printMatrix(matrix, n);

    printf("\nEnter the key to search: ");
    scanf("%d", &key);

    if (searchMatrix(matrix, n, key))
        printf("Key %d found.\n", key);
    else
        printf("Key %d not found.\n", key);

    return 0;
}
