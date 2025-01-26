#include <iostream>   // Para std::cout
#include <vector>     // Para std::vector
#include <cstdlib>    // Para rand(), srand()
#include <ctime>      // Para time()
#include <omp.h>      // Para programación paralela con OpenMP

constexpr std::size_t SIZE = 1000;  // Tamaño de los arreglos
constexpr std::size_t CHUNK = 100; // Tamaño de cada pedazo (chunk) para OpenMP
constexpr std::size_t SHOW = 10;   // Número de elementos a imprimir

/**
 * @brief Imprime los primeros elementos de un arreglo.
 * 
 * @param arr Arreglo a imprimir (std::vector<float>).
 * @param label Etiqueta descriptiva del arreglo (ej. "A").
 */
void imprimeArreglo(const std::vector<float>& arr, const std::string& label) {
    std::cout << label << ":\t";
    for (std::size_t i = 0; i < SHOW; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Declaración de los arreglos como std::vector para seguridad y flexibilidad
    std::vector<float> A(SIZE), B(SIZE), R(SIZE);

    // Inicializar el generador de números aleatorios con una semilla variable
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Llenar los arreglos A y B con valores aleatorios entre 0 y 99
    for (std::size_t i = 0; i < SIZE; i++) {
        A[i] = static_cast<float>(std::rand() % 100); // Convertir a float
        B[i] = static_cast<float>(std::rand() % 100);
    }

    /**
     * @brief Suma paralela de los arreglos A y B en C.
     * 
     * Directiva OpenMP:
     * - `parallel for`: Divide el bucle entre hilos.
     * - `num_threads(2)`: Usa exactamente 2 hilos.
     * - `schedule(static, CHUNK)`: Divide las iteraciones en bloques de tamaño CHUNK.
     * - `default(none)`: Obliga a declarar explícitamente las variables.
     * - `shared`: Variables compartidas entre hilos.
     */
    #pragma omp parallel for num_threads(2) schedule(static, CHUNK) \
    default(none) shared(A, B, R)
    for (std::size_t i = 0; i < SIZE; i++) {
        R[i] = A[i] + B[i];
    }

    // Imprimir los primeros 10 elementos de cada arreglo
    std::cout << "Primeros " << SHOW << " elementos de los arreglos:\n";
    imprimeArreglo(A, "A");
    imprimeArreglo(B, "B");
    imprimeArreglo(R, "R");

    return 0; // Indica que la ejecución fue exitosa
}
