#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int arr[], int n)
{
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
 
        if (swapped == false)
            break;
    }
}

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
}

int main() {
    int n = 0;
    
    printf("Insira o tamanho do vetor: ");
    scanf("%d", &n);

    int arr[n];
    srand(time(NULL));

    for(int i=0; i<n; i++) {
        arr[i] = rand() % 101;
    }

    printf("Antes da ordenacao: ");
    printArray(arr, n);
    printf("\n");
    printf("Apos a ordenacao: ");
    bubbleSort(arr, n);
    printArray(arr, n);

    return 0;
}