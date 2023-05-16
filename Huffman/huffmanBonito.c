#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Estructura de un nodo del arbol de Huffman
typedef struct nodo{
    unsigned char byte;
    int frecuencia;
    char *codigo;
    struct nodo *izquierda;
    struct nodo *derecha;
} Nodo;

//Estructura de una entrada de la tabla de codigos de Huffman
typedef struct codigo{
    unsigned char byte;
    char *codigo;
} Codigo;


//Prototipos de funciones
void crearArchivoTablaCodigos(Codigo *tablaCodigos);
void crearArchivoTablaFrecuencias(int *tablaFrecuencias);
Nodo *crearArbolHuffman(Nodo *listaNodos);
Nodo *crearListaNodos(int* frecuencias);
int *frecuencias(unsigned char *bytes, int tamano);

//Codigo que utiliza el algoritmo de Huffman para comprimir y descomprimir un archivo de e

int main(int argc, char *argv[]){

    if(argc != 2){
        printf("Se debe proporcionar un archivo de entrada\n");
        return 1;
    }


    //abrir archivo en modo lectura binaria
    FILE *archivo = fopen(argv[1], "rb");
    if(archivo == NULL){
        printf("No se pudo abrir el archivo\n");
        return 1;
    }


    //obtener tamaño del archivo
    fseek(archivo, 0, SEEK_END);
    int tamano = ftell(archivo);
    fseek(archivo, 0, SEEK_SET);


    //leer los bytes del archivo y los guarda en un arreglo
    unsigned char *bytes = malloc(tamano);
    fread(bytes, tamano, 1, archivo);

    int *tablaFrecuencias = frecuencias(bytes, tamano);

    /*En este punto ya tenemos los bytes del archivo en un arreglo
    * y tenemos un arreglo de frecuencias de cada byte
    */
    //*************************************************************

    //crear una lista de nodos con los bytes y sus frecuencias
    Nodo *lista = crearListaNodos(tablaFrecuencias);

    //crear un arbol de huffman a partir de la lista de nodos
    Nodo *raiz = crearArbolHuffman(lista);

    //crear una tabla de codigos de huffman a partir del arbol de huffman
    Codigo *tablaCodigos = crearTablaCodigos(raiz);

    //funcion para crear un archivo de texto con la tabla de codigos
    crearArchivoTablaCodigos(tablaCodigos);

    //funcion para crear un archivo de texto con la tabla de frecuencias
    crearArchivoTablaFrecuencias(tablaFrecuencias);

    //funcion para llenar la tabla de frecuencias con el archivo de texto
    int *tablaFrecuencias2;
    tablaFrecuencias2 = malloc(256 * sizeof(int));
    llenarTablaFrecuencias(tablaFrecuencias2);

    //crear un archivo comprimido a partir de la tabla de codigos y los bytes del archivo
    crearArchivoComprimido(tablaCodigos, bytes, tamano);

    //crear un archivo descomprimido a partir del archivo comprimido
    crearArchivoDescomprimido(tablaCodigos, bytes, tamano);


    return 0;
}

//funcion para llenar la tabla de frecuencias con el archivo de texto para utilizarla en la funcion crearArchivoDescomprimido
void llenarTablaFrecuencias(int *tablaFrecuencias){
    FILE *archivoTablaFrecuencias = fopen("tablaFrecuencias.txt", "r");
    if(archivoTablaFrecuencias == NULL){
        printf("No se pudo abrir el archivo de la tabla de frecuencias\n");
        return;
    }
    int byte, frecuencia;
    while(fscanf(archivoTablaFrecuencias, "%d %d\n", &byte, &frecuencia) != EOF){
        tablaFrecuencias[byte] = frecuencia;
    }
    fclose(archivoTablaFrecuencias);
}


//funcion para crear un archivo de texto con la tabla de frecuencias
void crearArchivoTablaFrecuencias(int *tablaFrecuencias){
    FILE *archivoTablaFrecuencias = fopen("tablaFrecuencias.txt", "w");
    if(archivoTablaFrecuencias == NULL){
        printf("No se pudo crear el archivo de la tabla de frecuencias\n");
        return;
    }
    for(int i = 0; i < 256; i++){
        if(tablaFrecuencias[i] != 0){
            fprintf(archivoTablaFrecuencias, "%d %d\n", i, tablaFrecuencias[i]);
        }
    }
    fclose(archivoTablaFrecuencias);
}

//funcion para crear un archivo de texto con la tabla de codigos
void crearArchivoTablaCodigos(Codigo *tablaCodigos){
    FILE *archivoTablaCodigos = fopen("tablaCodigos.txt", "w");
    if(archivoTablaCodigos == NULL){
        printf("No se pudo crear el archivo de la tabla de codigos\n");
        return;
    }
    for(int i = 0; i < 256; i++){
        if(tablaCodigos[i].codigo != NULL){
            fprintf(archivoTablaCodigos, "%d %s\n", tablaCodigos[i].byte, tablaCodigos[i].codigo);
        }
    }
    fclose(archivoTablaCodigos);
}


/*
DESCRIPCION DE LA FUNCION crearArchivoComprimido: 
    Esta funcion crea un archivo comprimido a partir de una tabla de codigos y los bytes del archivo

ENTRADA:
    tablaCodigos: tabla de codigos de Huffman
    bytes: arreglo de bytes del archivo
    tamano: tamaño del archivo

SALIDA:
    archivoComprimido: archivo comprimido
*/

//Funcion que crea un archivo descomprimido a partir de una tabla de codigos, los bytes del archivo y el tamaño del archivo
void crearArchivoDescomprimido(Codigo *tablaCodigos, unsigned char *bytes, int tamano){
    FILE *archivoDescomprimido = fopen("archivoDescomprimido.dat", "wb");
    if(archivoDescomprimido == NULL){
        printf("No se pudo crear el archivo descomprimido\n");
        return;
    }
    int tamanoArchivoDescomprimido = 0;
    for(int i = 0; i < tamano; i++){
        tamanoArchivoDescomprimido += strlen(tablaCodigos[bytes[i]].codigo);
    }
    unsigned char *bytesArchivoDescomprimido = malloc(tamanoArchivoDescomprimido);
    int indice = 0;
    for(int i = 0; i < tamano; i++){
        for(int j = 0; j < strlen(tablaCodigos[bytes[i]].codigo); j++){
            bytesArchivoDescomprimido[indice] = tablaCodigos[bytes[i]].codigo[j];
            indice++;
        }
    }
    fwrite(bytesArchivoDescomprimido, tamanoArchivoDescomprimido, 1, archivoDescomprimido);
    fclose(archivoDescomprimido);
}

//Funcion que crea un archivo binario comprimido a partir de una tabla de codigos y los bytes del archivo
void crearArchivoComprimido(Codigo *tablaCodigos, unsigned char *bytes, int tamano){
    FILE *archivoComprimido = fopen("archivoComprimido.dat", "wb");
    if(archivoComprimido == NULL){
        printf("No se pudo crear el archivo comprimido\n");
        return;
    }
    int tamanoArchivoComprimido = 0;
    for(int i = 0; i < tamano; i++){
        tamanoArchivoComprimido += strlen(tablaCodigos[bytes[i]].codigo);
    }
    unsigned char *bytesArchivoComprimido = malloc(tamanoArchivoComprimido);
    int indice = 0;
    for(int i = 0; i < tamano; i++){
        for(int j = 0; j < strlen(tablaCodigos[bytes[i]].codigo); j++){
            bytesArchivoComprimido[indice] = tablaCodigos[bytes[i]].codigo[j];
            indice++;
        }
    }
    fwrite(bytesArchivoComprimido, tamanoArchivoComprimido, 1, archivoComprimido);
    fclose(archivoComprimido);
}


/*
DESCRIPCION DE LA FUNCION crearTablaCodigos: 
    Esta funcion crea una tabla de codigos de Huffman a partir de un arbol de Huffman

ENTRADA:
    raiz: puntero a la raiz del arbol de Huffman

SALIDA:
    tablaCodigos: tabla de codigos de Huffman

*/
//Funcion que crea una tabla de codigos de Huffman a partir de un arbol de Huffman
Codigo *crearTablaCodigos(Nodo *raiz){
    Codigo *tablaCodigos = malloc(sizeof(Codigo) * 256);
    char *codigo = malloc(sizeof(char) * 256);
    crearTablaCodigosAux(raiz, tablaCodigos, codigo);
    return tablaCodigos;
}


/*
DESCRIPCION DE LA FUNCION crearTablaCodigosAux: 
    Esta funcion crea una tabla de codigos de Huffman a partir de un arbol de Huffman

ENTRADA:
    nodo: puntero a un nodo del arbol de Huffman
    tablaCodigos: tabla de codigos de Huffman
    codigo: codigo de Huffman del nodo

SALIDA:
    tablaCodigos: tabla de codigos de Huffman
*/

//Funcion auxiliar para crear una tabla de codigos de Huffman a partir de un arbol de Huffman
void crearTablaCodigosAux(Nodo *nodo, Codigo *tablaCodigos, char *codigo){
    if(nodo->izquierda == NULL && nodo->derecha == NULL){
        tablaCodigos[nodo->byte].byte = nodo->byte;
        tablaCodigos[nodo->byte].codigo = codigo;
    }else{
        char *codigoIzquierda = malloc(sizeof(char) * 256);
        strcpy(codigoIzquierda, codigo);
        strcat(codigoIzquierda, "0");
        crearTablaCodigosAux(nodo->izquierda, tablaCodigos, codigoIzquierda);

        char *codigoDerecha = malloc(sizeof(char) * 256);
        strcpy(codigoDerecha, codigo);
        strcat(codigoDerecha, "1");
        crearTablaCodigosAux(nodo->derecha, tablaCodigos, codigoDerecha);
    }
}


/*
DESCRIPCION DE LA FUNCION frecuencias: 
    Esta funcion crea una tabla de frecuencias de cada byte del archivo

ENTRADA:
    bytes: arreglo de bytes del archivo
    tamano: tamaño del archivo  

SALIDA:
    frecuencias: tabla de frecuencias de cada byte del archivo

*/
//funcion que creará una tabla de frecuencias de cada byte del archivo
int *frecuencias(unsigned char *bytes, int tamano){
    int *frecuencias = calloc(256, sizeof(int));
    for(int i = 0; i < tamano; i++){
        frecuencias[bytes[i]]++;
    }
    return frecuencias;
}

/*
DESCRIPCION DE LA FUNCION crearListaNodos: 
    Esta funcion crea una lista de nodos a partir de una tabla de frecuencias de los bytes del archivo.
    La lista de nodos estará ordenada de menor a mayor frecuencia
ENTRADA: 
   frecuencias: tabla de frecuencias de los bytes del archivo

SALIDA:
    lista: puntero al primer nodo de la lista de nodos creada

*/

//Funcion para crear una lista de nodos con los bytes y sus frecuencias de manera ordenada a partir de una tabla de frecuencias 
Nodo *crearListaNodos(int* frecuencias){
    //crea una lista vacia
    Nodo *lista = NULL;
    Nodo *nuevoNodo = NULL;
    Nodo *nodoActual = NULL;

    //recorre la tabla de frecuencias
    for(int i = 0; i < 256; i++){
        //si la frecuencia es mayor a 0, crea un nodo y lo agrega a la lista
        if(frecuencias[i] > 0){
            nuevoNodo = malloc(sizeof(Nodo));
            nuevoNodo->byte = (unsigned char)i;
            nuevoNodo->frecuencia = frecuencias[i];
            nuevoNodo->izquierda = NULL;
            nuevoNodo->derecha = NULL;
            nuevoNodo->codigo = NULL;

            //Insertar el nuevo nodo en la lista de manera ordenada de menor a mayor frecuencia
            //si la lista esta vacia o la frecuencia del nuevo nodo es menor a la del primer nodo de la lista, se agrega al inicio

            if(lista == NULL || lista->frecuencia > nuevoNodo->frecuencia){
                nuevoNodo->izquierda = lista;
                lista = nuevoNodo;

            }else{
                nodoActual = lista;
                while(nodoActual->derecha != NULL && nodoActual->derecha->frecuencia <= frecuencias[i]){
                    nodoActual = nodoActual->derecha;
                }
                nuevoNodo->izquierda = nodoActual->derecha;
                nodoActual->derecha = nuevoNodo;
            }
        }
    }
    return lista;

}

/*
DESCRIPCION DE LA FUNCION crearArbolHuffman: 
    Esta funcion crea un arbol binario a partir de la implementacion del algoritmo 
    de Huffmana partir de una lista de nodos ordenada de menor a mayor frecuencia

ENTRADA: 
   listaNodos: lista de nodos ordenada de menor a mayor frecuencia

SALIDA:
    raiz: puntero a la raiz del arbol de Huffman creado
*/

//funcion que crea un arbol de huffman a partir de una lista de nodos
Nodo *crearArbolHuffman(Nodo *listaNodos){
    Nodo *nodoActual = listaNodos;
    Nodo *nuevoNodo = NULL;
    Nodo *nodoIzquierda = NULL;
    Nodo *nodoDerecha = NULL;

    //mientras la lista tenga mas de un nodo se creara un nuevo nodo con la suma de las frecuencias de los dos primeros nodos de la lista
    while(nodoActual->derecha != NULL){
        //crea un nuevo nodo y le asigna la suma de las frecuencias mas bajas de la lista
        nuevoNodo = malloc(sizeof(Nodo));
        nuevoNodo->byte = 0;
        nuevoNodo->frecuencia = nodoActual->frecuencia + nodoActual->derecha->frecuencia;
        nuevoNodo->izquierda = nodoActual;
        nuevoNodo->derecha = nodoActual->derecha;
        nuevoNodo->codigo = NULL;

        //elimina los dos primeros nodos de la lista y los reemplaza por el nuevo nodo que ya los contiene como hijos
        listaNodos = listaNodos->derecha->derecha;

        //inserta el nuevo nodo en la lista de manera ordenada
        if(listaNodos == NULL || listaNodos->frecuencia > nuevoNodo->frecuencia){
            nuevoNodo->derecha = listaNodos;
            listaNodos = nuevoNodo;
        }else{
            nodoActual = listaNodos;
            while(nodoActual->derecha != NULL && nodoActual->derecha->frecuencia <= nuevoNodo->frecuencia){
                nodoActual = nodoActual->derecha;
            }
            nuevoNodo->derecha = nodoActual->derecha;
            nodoActual->derecha = nuevoNodo;
        }
    }

    //retorna el ultimo nodo de la lista que es la raiz del arbol y contiene todos los demas nodos como hijos
    return listaNodos;
}
