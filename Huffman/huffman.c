#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_BYTES 256 // número máximo de bytes diferentes (0-255)

typedef struct NodoHuffman {
    unsigned char byte; // byte representado por el nodo
    int frecuencia; // frecuencia del byte
    struct NodoHuffman *izquierdo; // puntero al nodo hijo izquierdo
    struct NodoHuffman *derecho; // puntero al nodo hijo derecho
}nodo;


typedef struct {
    unsigned char byte;
    int frecuencia;
} frecuencia_byte;


typedef struct {
    int tamano;
    frecuencia_byte *tabla;
} tabla_frecuencia;


void descomprimir(FILE *archivo_comprimido, FILE *archivo_descomprimido);
void guardar_codigos(nodo *raiz, char *codigo, char **codigos);
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
    char *codigos[MAX_BYTES] = {0};
    FILE *salida = fopen("archivo_comprimido.dat", "wb");

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


    // Generar los códigos para cada byte
    char codigo[MAX_BYTES] = {0};
    guardar_codigos(arbolote, codigo, codigos);


   //tabla_frecuencia *tabla = generar_tabla_frecuencia(archivo);

    // imprimir los códigos de Huffman para cada byte
    for (int i = 0; i < MAX_BYTES; i++) {
        if (codigos[i] != NULL) {
            printf("%02X %s\n", i, codigos[i]);
        }
    }

    // Escribir el archivo comprimido en el archivo de salida (archivo_comprimido.dat) pero que este archivo sea binario

    // Escribir el tamaño del archivo original  
    fwrite(&tamaño, sizeof(long), 1, salida);

    // Escribir la tabla de frecuencias
    for (int i = 0; i < MAX_BYTES; i++) {
        if (frecuencias[i] != 0) {
            fwrite(&i, sizeof(char), 1, salida);
            fwrite(&frecuencias[i], sizeof(int), 1, salida);
        }
    }



    // Escribir el archivo comprimido
    char buffer = 0;
    int contador_bits = 0;
    for (int i = 0; i < tamaño; i++) {
        char *codigo = codigos[(unsigned char) bytes[i]];
        for (int j = 0; j < strlen(codigo); j++) {
            if (codigo[j] == '1') {
                buffer |= 1 << (7 - contador_bits);
            }
            contador_bits++;
            if (contador_bits == 8) {
                fwrite(&buffer, sizeof(char), 1, salida);
                buffer = 0;
                contador_bits = 0;
            }
        }
    }

    // Escribir el último byte
    if (contador_bits > 0) {
        fwrite(&buffer, sizeof(char), 1, salida);
    }

    //crear el archivo descomprimido
   FILE *archivo_descomprimido = fopen("archivo_descomprimido.txt", "w");
    //llamada a la funcion de descomprimir
    descomprimir(salida, archivo_descomprimido);
    

    fclose(salida); // cerrar el archivo de salida
    free(bytes); // liberar la memoria asignada para el arreglo

    return 0;
}


//descomprimir el archivo comprimido con el archivo comprimido
void descomprimir(FILE *archivo_comprimido, FILE *archivo_descomprimido){
    long tam_original;
    fread(&tam_original, sizeof(long), 1, archivo_comprimido);

    int frecuencias[MAX_BYTES] = {0};
    char byte;
    int frecuencia;

    // Leer la tabla de frecuencias
    while (fread(&byte, sizeof(char), 1, archivo_comprimido) == 1) {
        fread(&frecuencia, sizeof(int), 1, archivo_comprimido);
        frecuencias[(unsigned char) byte] = frecuencia;
    }

    // Crear un arreglo de nodos para cada byte en el archivo
    int tamNodos = 0;
    for (int i = 0; i < MAX_BYTES; i++) {
        if (frecuencias[i] > 0) {
            tamNodos++;
        }
    }
    
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

    // Descomprimir el archivo comprimido
    char buffer;
    nodo *nodo_actual = arbolote;
    long contador_bytes = 0;

    while (contador_bytes < tam_original) {
        fread(&buffer, sizeof(char), 1, archivo_comprimido);
        for (int i = 0; i < 8; i++) {
            if (buffer & (1 << (7 - i))) {
                nodo_actual = nodo_actual->derecho;
            } else {
                nodo_actual = nodo_actual->izquierdo;
            }
            if (nodo_actual->izquierdo == NULL && nodo_actual->derecho == NULL) {
                fwrite(&nodo_actual->byte, sizeof(char), 1, archivo_descomprimido);
                nodo_actual = arbolote;
                contador_bytes++;
                if (contador_bytes == tam_original) {
                    break;
                }
            }
        }
    }

    fclose(archivo_descomprimido);



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

//Guardar los códigos de Huffman en un arreglo de bits
void guardar_codigos(nodo *raiz, char *codigo, char **codigos) {
    if (raiz != NULL) {
        if (raiz->izquierdo == NULL && raiz->derecho == NULL) {
            codigos[(unsigned char) raiz->byte] = (char *) malloc(strlen(codigo) + 1);
            strcpy(codigos[(unsigned char) raiz->byte], codigo);
        }
        else {
            char codigo_izq[strlen(codigo) + 2];
            strcpy(codigo_izq, codigo);
            strcat(codigo_izq, "0");
            guardar_codigos(raiz->izquierdo, codigo_izq, codigos);

            char codigo_der[strlen(codigo) + 2];
            strcpy(codigo_der, codigo);
            strcat(codigo_der, "1");
            guardar_codigos(raiz->derecho, codigo_der, codigos);
        }
    }
}
/*
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

*/


// Genera una tabla de frecuencias a partir de un archivo
//******************************************************************************
/*tabla_frecuencia *generar_tabla_frecuencia(char *nombre_archivo) {
    FILE *archivo;
    unsigned char byte;
    tabla_frecuencia *tabla;
    frecuencia_byte *tabla_bytes;
    int tamano_tabla = 0, i, j, encontrado;

    archivo = fopen(nombre_archivo, "rb");

    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return NULL;
    }

    tabla_bytes = (frecuencia_byte *) malloc(sizeof(frecuencia_byte));
    tamano_tabla++;

    while (fread(&byte, sizeof(unsigned char), 1, archivo)) {
        encontrado = 0;

        for (i = 0; i < tamano_tabla; i++) {
            if (tabla_bytes[i].byte == byte) {
                tabla_bytes[i].frecuencia++;
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            tabla_bytes = (frecuencia_byte *) realloc(tabla_bytes, (tamano_tabla + 1) * sizeof(frecuencia_byte));
            tabla_bytes[tamano_tabla].byte = byte;
            tabla_bytes[tamano_tabla].frecuencia = 1;
            tamano_tabla++;
        }
    }

    tabla = (tabla_frecuencia *) malloc(sizeof(tabla_frecuencia));
    tabla->tamano = tamano_tabla;
    tabla->tabla = tabla_bytes;

    fclose(archivo);

    return tabla;
}

*/
