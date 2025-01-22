#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 1000

int main() {
    int a[SIZE], b[SIZE], c[SIZE];

    // Generar valores aleatorios para los arreglos
    for (int i = 0; i < SIZE; i++) {
        a[i] = rand() % 100;  // Valores aleatorios entre 0 y 99
        b[i] = rand() % 100;
    }

    // Paralelizar el bucle para sumar los arreglos
    #pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
        c[i] = a[i] + b[i];
    }

    // Imprimir los primeros 10 elementos de cada arreglo
    printf("Primeros 10 elementos de A, B y C:\n");
    for (int i = 0; i < 10; i++) {
        printf("A[%d]=%d, B[%d]=%d, C[%d]=%d\n", i, a[i], i, b[i], i, c[i]);
    }

    return 0;
}

