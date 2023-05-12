#include <stdio.h>
#include <stdlib.h>

#define MAX_BYTES 256 // número máximo de bytes diferentes (0-255)


struct NodoHuffman {
    unsigned char byte;
    int frecuencia;
    struct NodoHuffman *izquierdo;
    struct NodoHuffman *derecho;
};

// Ordena los nodos por frecuencia de menor a mayor
void ordenar_nodos(struct NodoHuffman *nodos, int tamano);

int main() {
    char *filename = "archivo.bin"; // nombre del archivo a leer
    FILE *file = fopen(filename, "rb"); // abrir el archivo en modo de lectura binaria

    if (file == NULL) { // verificar si se pudo abrir el archivo
        printf("No se pudo abrir el archivo\n");
        return 1;
    }

    char byte;
    long size = 0;
    char *bytes = NULL;
    int frecuencias[MAX_BYTES] = {0}; // arreglo para almacenar las frecuencias de cada byte

    // obtener los bytes del archivo y las frecuencias de cada byte
    while ((byte = fgetc(file)) != EOF) {
        size++;
        bytes = (char *) realloc(bytes, size); // asignar más memoria al arreglo
        bytes[size - 1] = byte;
        frecuencias[(unsigned char) byte]++;
    }

    fclose(file); // cerrar el archivo

    // imprimir los bytes del archivo
    for (int i = 0; i < size; i++) {
        printf("%02X ", bytes[i]);
    }
    printf("\n");

    FILE *freq_file = fopen("frecuencias.txt", "w"); // abrir el archivo para escribir las frecuencias

    // imprimir las frecuencias de cada byte
    for (int i = 0; i < MAX_BYTES; i++) {
        if (frecuencias[i] > 0) {
            printf("%d: %d\n", i, frecuencias[i]);
        }
    }
        
    fclose(freq_file); // cerrar el archivo de frecuencias
    
    // crear un arreglo de nodos para cada byte en el archivo
    struct NodoHuffman *nodos[MAX_BYTES];
    for (int i = 0; i < MAX_BYTES; i++) {
        if (frecuencias[i] > 0) {
            nodos[i] = (struct NodoHuffman*) malloc(sizeof(struct NodoHuffman));
            nodos[i]->byte = i;
            nodos[i]->frecuencia = frecuencias[i];
            nodos[i]->izquierdo = NULL;
            nodos[i]->derecho = NULL;
        } else {
            nodos[i] = NULL;
        }
    }
    
    free(bytes); // liberar la memoria asignada para el arreglo

    return 0;
}

// Ordena los nodos por frecuencia de menor a mayor
void ordenar_nodos(struct NodoHuffman *nodos, int tamano) {
    int i, j;
    struct NodoHuffman temp;
    
    for (i = 0; i < tamano - 1; i++) {
        for (j = 0; j < tamano - i - 1; j++) {
            if (nodos[j].frecuencia > nodos[j+1].frecuencia) {
                temp = nodos[j];
                nodos[j] = nodos[j+1];
                nodos[j+1] = temp;
            }
        }
    }
}
