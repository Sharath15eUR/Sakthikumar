#include <stdio.h>
#include <stdlib.h>

// Rearranging array so that even numbers come first, preserving relative order
void rearrange(int *arr, int size) {
    int *temp = (int *)malloc(size * sizeof(int));
    if (temp == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    int *writePtr = temp;

    // Copying even numbers first
    for (int *ptr = arr; ptr < arr + size; ptr++) {
        if (*ptr % 2 == 0) {
            *writePtr = *ptr;
            writePtr++;
        }
    }

    // Then Copying odd numbers
    for (int *ptr = arr; ptr < arr + size; ptr++) {
        if (*ptr % 2 != 0) {
            *writePtr = *ptr;
            writePtr++;
        }
    }

    // Copying back to the original array
    for (int i = 0; i < size; i++) {
        *(arr + i) = *(temp + i);
    }

    free(temp);
}

// Printing array values using pointer arithmetic
void printArray(const int *arr, int size) {
    for (const int *ptr = arr; ptr < arr + size; ptr++) {
        printf("%d ", *ptr);
    }
    printf("\n");
}

int main() {
    int size;

    printf("Enter the number of elements: ");
    scanf("%d", &size);

    if (size <= 0) {
        printf("Invalid array size.\n");
        return 1;
    }

    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d integers:\n", size);
    for (int *ptr = arr; ptr < arr + size; ptr++) {
        scanf("%d", ptr);
    }

    printf("\nOriginal:   ");
    printArray(arr, size);

    rearrange(arr, size);

    printf("Rearranged: ");
    printArray(arr, size);

    free(arr);
    return 0;
}
