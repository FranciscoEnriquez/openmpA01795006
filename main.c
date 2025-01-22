#include <stdio.h>
#include <stdlib.h> // Para usar rand() y srand()
#include <omp.h>    // Para la programación paralela con OpenMP

#define SIZE 1000 // Tamaño del arreglo

int main() {
    int A[SIZE], B[SIZE], R[SIZE]; // Declaración de los arreglos

    // Inicializar el generador de números aleatorios
    srand(42); // Usar una semilla fija para resultados reproducibles

    // Generar valores aleatorios para los arreglos A y B
    for (int i = 0; i < SIZE; i++) {
        A[i] = rand() % 100; // Valores entre 0 y 99
        B[i] = rand() % 100; // Valores entre 0 y 99
    }

    // Sumar los arreglos en paralelo usando 2 threads
    #pragma omp parallel for num_threads(2) // Usar 2 threads
    for (int i = 0; i < SIZE; i++) {
        R[i] = A[i] + B[i];
    }

    // Imprimir una parte de los arreglos para verificar
    printf("Primeros 10 elementos de los arreglos:\n");
    printf("A:\t");
    for (int i = 0; i < 10; i++) {
        printf("%d ", A[i]);
    }

    printf("\nB:\t");
    for (int i = 0; i < 10; i++) {
        printf("%d ", B[i]);
    }

    printf("\nR:\t");
    for (int i = 0; i < 10; i++) {
        printf("%d ", R[i]);
    }

    printf("\n");

    return 0;
}