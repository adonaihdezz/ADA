#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BYTES 256 // número máximo de bytes diferentes (0-255)

typedef struct NodoHuffman {
    unsigned char byte; // byte representado por el nodo
    int frecuencia; // frecuencia del byte
    struct NodoHuffman *izquierdo; // puntero al nodo hijo izquierdo
    struct NodoHuffman *derecho; // puntero al nodo hijo derecho
}nodo;


void imprimir_arbol_huffman(nodo *raiz, char *codigo);
void ordenar_nodos(nodo **nodos, int tamano);
nodo *crear_arbol_huffman(nodo **nodos, int tamano);

int main(int argc, char *argv[]) {
    // Verificar que se ha proporcionado el nombre del archivo
    if (argc != 2) {
        printf("Uso: %s <nombre del archivo>\n", argv[0]);
        return 1;
    }

    // Abrir el archivo en modo de lectura binaria
    FILE *archivo = fopen(argv[1], "rb");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo\n");
        return 1;
    }

    //char byte;
    long size = 0;
    char *bytes = NULL;
    int frecuencias[MAX_BYTES] = {0}; // arreglo para almacenar las frecuencias de cada byte

    // obtener los bytes del archivo y las frecuencias de cada byte

    // Obtener el tamaño del archivo
    fseek(archivo, 0, SEEK_END);
    long tamaño = ftell(archivo);
    fseek(archivo, 0, SEEK_SET);

    // Verificar si el archivo está vacío
    if (tamaño == 0) {
        printf("El archivo está vacío\n");
        return 1;
    }

    // Asignar memoria para almacenar los bytes del archivo
    bytes = (char *) malloc(tamaño);
    if (bytes == NULL) {
        printf("No se pudo asignar memoria\n");
        return 1;
    }

    // Leer los bytes del archivo
    size_t bytes_leidos = fread(bytes, 1, tamaño, archivo);

    // Verificar si se leyeron todos los bytes esperados
    if (bytes_leidos != tamaño) {
        printf("Error al leer el archivo\n");
        return 1;
    }


    // Leer los bytes del archivo
    fread(bytes, 1, tamaño, archivo);

    // Contar las frecuencias de los bytes
    for (int i = 0; i < tamaño; i++) {
        frecuencias[(unsigned char) bytes[i]]++;
    }

    int tamNodos = 0;
    for (int i = 0; i < MAX_BYTES; i++) {
        if (frecuencias[i] > 0) {
            tamNodos++;
        }
    }

    fclose(archivo); // cerrar el archivo

    FILE *freq_archivo = fopen("frecuencias.txt", "w"); // abrir el archivo para escribir las frecuencias

    // escribir las frecuencias en el archivo
    for (int i = 0; i < MAX_BYTES; i++) {
        if (frecuencias[i] != 0) {
            fprintf(freq_archivo, "%02X %d\n", i, frecuencias[i]);
        }
    }
        
    fclose(freq_archivo); // cerrar el archivo de frecuencias
    
    // crear un arreglo de nodos para cada byte en el archivo
    nodo *nodos[tamNodos];
    int contador = 0; // contador para llenar el arreglo de nodos

    for (int i = 0; i < MAX_BYTES; i++) {
        if (frecuencias[i] > 0) {
            nodos[contador] = (nodo *) malloc(sizeof(nodo));
            nodos[contador]->byte = i;
            nodos[contador]->frecuencia = frecuencias[i];
            nodos[contador]->izquierdo = NULL;
            nodos[contador]->derecho = NULL;
            contador++;
        }
    }

    // Crear el árbol de Huffman
    nodo *arbolote = crear_arbol_huffman(nodos, tamNodos);


    // Imprimir el árbol de Huffman en la consola
    imprimir_arbol_huffman(arbolote, "");

    
    free(bytes); // liberar la memoria asignada para el arreglo

    return 0;
}


// Ordena los nodos por frecuencia de menor a mayor
void ordenar_nodos(nodo **nodos, int tamano){
    for (int i = 0; i < tamano - 1; i++) {
        for (int j = 0; j < tamano - i - 1; j++) {
            if (nodos[j]->frecuencia > nodos[j+1]->frecuencia) {
                nodo *temp = nodos[j];
                nodos[j] = nodos[j+1];
                nodos[j+1] = temp;
            }
        }
    }
}
// Crear un árbol de Huffman a partir de los nodos
// Crear un árbol de Huffman a partir de los nodos
nodo *crear_arbol_huffman(nodo **nodos, int tamano) {
    // Ordenar los nodos por frecuencia de menor a mayor
    ordenar_nodos(nodos, tamano);
    
    while (tamano > 1) {
        // Tomar los dos nodos con frecuencias más bajas
        nodo *izquierdo = nodos[0];
        nodo *derecho = nodos[1];
        
        // Crear un nuevo nodo que tenga como hijo izquierdo el nodo con frecuencia más baja
        // y como hijo derecho el nodo con la siguiente frecuencia más baja
        nodo *nuevo = (nodo*) malloc(sizeof(nodo));
        nuevo->byte = -1;
        nuevo->frecuencia = izquierdo->frecuencia + derecho->frecuencia;
        nuevo->izquierdo = izquierdo;
        nuevo->derecho = derecho;
        
        // Reemplazar los dos nodos más bajos con el nuevo nodo
        nodos[0] = nuevo;
        for (int i = 1; i < tamano - 1; i++) {
            nodos[i] = nodos[i+1];
        }
        tamano--;
        
        // Ordenar los nodos de nuevo
        ordenar_nodos(nodos, tamano);
    }
    
    // El último nodo restante es la raíz del árbol de Huffman
    return nodos[0];
}

// Imprime el árbol de Huffman en preorden
void imprimir_arbol_huffman(nodo *raiz, char *codigo) {
    if (raiz != NULL) {
        if (raiz->izquierdo == NULL && raiz->derecho == NULL) {
            printf("%c: %s\n", raiz->byte, codigo);
        }
        else {
            char codigo_izq[strlen(codigo) + 2];
            strcpy(codigo_izq, codigo);
            strcat(codigo_izq, "0");
            imprimir_arbol_huffman(raiz->izquierdo, codigo_izq);

            char codigo_der[strlen(codigo) + 2];
            strcpy(codigo_der, codigo);
            strcat(codigo_der, "1");
            imprimir_arbol_huffman(raiz->derecho, codigo_der);
        }
    }
}

