/*ESTA PEQUEÑA PARTE DEL CODIGO HACE LA LECTURA DEL ARCHIVO Y CON UN BUCLE WHILE
*DETECTA LOS BYTES QUE TIENE ESTE, DONDE LOS GUARDA EN UN ARREGLO DE CHARS Y CON ESE 
*MISMO ARREGLO DE CHARS GUARDA EN OTRO ARREGLO LAS FRECUENCIA DE LOS BYTES
*/


#include <stdio.h>
#include <stdlib.h>

#define MAX_BYTES 256 // número máximo de bytes diferentes (0-255)

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
    int frequencies[MAX_BYTES] = {0}; // arreglo para almacenar las frecuencias de cada byte

    // obtener los bytes del archivo y las frecuencias de cada byte
    while ((byte = fgetc(file)) != EOF) {
        size++;
        bytes = (char *) realloc(bytes, size); // asignar más memoria al arreglo
        bytes[size - 1] = byte;
        frequencies[(unsigned char) byte]++;
    }

    fclose(file); // cerrar el archivo

    // imprimir los bytes del archivo
    for (int i = 0; i < size; i++) {
        printf("%02X ", bytes[i]);
    }
    printf("\n");

    // imprimir las frecuencias de cada byte
    for (int i = 0; i < MAX_BYTES; i++) {
        if (frequencies[i] > 0) {
            printf("%02X: %d\n", i, frequencies[i]);
        }
    }

    free(bytes); // liberar la memoria asignada para el arreglo

    return 0;
}

