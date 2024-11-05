#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
Funcion para encontrar la longitud de la linea mas larga de 1s en una matriz
- No retorna un valor, pero modifica el valor en result.
*/
void findLargestLine(int **matrix, int size, int *result) {
    *result = 0; // Se inicializa un puntero 
    int currentCount = 0; // Se declara la variable

    // Buscar secuencias en la matriz por medio de bucles y reccoriendo por fila y columna 
    for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
    if (*(*(matrix + i) + j) == 1) { //Esta condición evalúa si la posición de la matriz es 1
    currentCount++; // Aumentando el contador
    } else {  // Si encontramos un cero, actualizamos el resultado si es necesario
    if (currentCount > *result) { /*Se verifica si la longitud actual es mayor que la más larga encontrada*/
    *result = currentCount;// Se actualiza de ser necesario
     }
    currentCount = 0; // Reiniciar el contador si se encuentra un 0
     }
     }

  }
}

/*
Funcion para reservar la matriz en memoria dinamica.

- No retorna un valor. Reserva memoria para la matriz.
*/
void allocateMatrix(int ***matrix, int size) {
    *matrix = malloc(size * sizeof(int *)); // Reservar espacio para las filas
    for (int i = 0; i < size; i++) { 
    (*matrix)[i] = malloc(size * sizeof(int)); // Reservar espacio para las columnas
    }
}

/*
Funcion para llenar la matriz con numeros aleatorios (0s y 1s).
- No retorna un valor. Llena la matriz con valores aleatorios.
*/
void fillMatrix(int **matrix, int size) {
    srand(time(0)); // Inicializar generador de números aleatorios
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            *(*(matrix + i) + j) = rand() % 2; // Llenar la matriz con 0s y 1s
        }
    }
}

/*
Funcion para imprimir la matriz.
- No retorna un valor. Imprime la matriz en la salida estandar.
*/
void printMatrix(int **matrix, int size) {
    printf("Matriz (%dx%d):\n", size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", *(*(matrix + i) + j)); // Imprimir cada elemento
        }
        printf("\n");
    }
}

/*
Funcion para liberar la memoria asignada a la matriz.
- No retorna un valor. Libera la memoria utilizada por la matriz.
*/
void freeMatrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]); // Libera cada fila
    }
    free(matrix); // Libera al puntero a filas
}

/*
Funcion para transponer la matriz.
- No retorna un valor. Transpone la matriz.
*/
void transposeMatrix(int **matrix, int size, int ***transposed) {
    allocateMatrix(transposed, size); // Reservar memoria para la matriz transpuesta
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            *(*(*transposed + j) + i) = *(*(matrix + i) + j); // Transponer los elementos correctamente
        }
    }
}

int main() {
    int size, largestLine;
    int **matrix = NULL;
    int **transposedMatrix = NULL;


    printf("Ingrese el tamaño de la matriz cuadrada: "); // Solicitar el tamaño de la matriz
    scanf("%d", &size);

    // LLamado de funciones
    allocateMatrix(&matrix, size);

    fillMatrix(matrix, size);

    printMatrix(matrix, size);

    findLargestLine(matrix, size, &largestLine);
    printf("La longitud de la secuencia de 1s más larga es: %d\n", largestLine);

    transposeMatrix(matrix, size, &transposedMatrix);

    printMatrix(transposedMatrix, size);

    largestLine = 0; // Reiniciar la longitud más larga para la matriz transpuesta
    findLargestLine(transposedMatrix, size, &largestLine); // Encuentra la secuencia más larga en la transpuesta
    printf("La longitud de la secuencia de 1s más larga en la matriz transpuesta es: %d\n", largestLine);

    // Liberar la memoria
    freeMatrix(matrix, size);
    freeMatrix(transposedMatrix, size);

    return 0;
}

