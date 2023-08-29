#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void random(int arr[], int n);
void ordenar(int arr[], int n);

int main() {
    srand(time(NULL));

    int n = 10;
    int arr[n];

    random(arr, n);

    printf("Arreglo original: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    ordenar(arr, n);

    printf("Arreglo ordenado: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
void random(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100; // 0 - 99
    }
}

void ordenar(int arr[], int n) {
   
    for (int i = 0; i < n - 1 ; i++) {
        int indiceMinimo = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[indiceMinimo]) {
                indiceMinimo = j;
            }
        }
        if (indiceMinimo != i) {
            int temp = arr[i];
            arr[i] = arr[indiceMinimo];
            arr[indiceMinimo] = temp;   
        }
    }
    
}
