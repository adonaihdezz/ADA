#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Cosas que hacer para completar el codigo de compresion y descompresion de Huffman
1. Crear una tabla de frecuencias de los bytes del archivo -> listo
2. Crear una lista de nodos con los bytes y sus frecuencias -> listo
3. Crear un arbol de huffman a partir de la lista de nodos -> listo
4. Crear una tabla de codigos de huffman a partir del arbol de huffman -> listo
5. Crear un archivo de texto con la tabla de codigos -> listo
6. calcular el tamaño que tendra el archivo comprimido -> listo
7. crear un arreglo de bytes que contendra el archivo comprimido -> listo
8. crear un archivo comprimido a partir del arreglo de bytes que contiene el archivo comprimido -> listo
9. crear un archivo de texto con la tabla de frecuencias, los bits del archivo comprimido y la cantidad de bytes del archivo original -> listo
10. empezar a descomprimir el archivo -> en proceso

*/

//Estructura de un nodo del arbol de Huffman
typedef struct nodo{
    unsigned char byte;
    int frecuencia;
    unsigned char *codigo;
    struct nodo *izquierda;
    struct nodo *derecha;
} Nodo;

//Prototipos de funciones
void crearArchivoTablaFrecuencias(char *nombreArchivo, int *frecuencias);
Nodo *crearArbolHuffman(Nodo *listaNodos);
Nodo *crearListaNodos(int* frecuencias);
int *frecuencias(unsigned char *bytes, int tamano);
char **crearTablaCodigos(Nodo *raiz);
void crearTablaCodigosAux(Nodo *nodo, char **tablaCodigos, char *codigo);
int calcularCantidadBytesArchivoComprimido(int *frecuencias, char **tablaCodigos);
char *crearArregloBytesArchivoComprimido(char *nombreArchivo, char **tablaCodigos, int cantidadBytesArchivoComprimido);
void crearArchivoComprimido(char *arregloBytesArchivoComprimido);


//Codigo que utiliza el algoritmo de Huffman para comprimir y descomprimir un archivo de cualquier tipo, no solo texto, ya sea .jpg, .bmp, .txt, etc.

int cantidadBytes2=0;

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
    char **tablaCodigos = crearTablaCodigos(raiz);

    //calcular el tamaño que tendra el archivo comprimido
    int tamanoNuevo = calcularCantidadBytesArchivoComprimido(tablaFrecuencias, tablaCodigos);

    //crear un arreglo de bytes que contendra el archivo comprimido
    char *arregloBytesArchivoComprimido = crearArregloBytesArchivoComprimido(argv[1], tablaCodigos, tamanoNuevo);


    //crear un archivo comprimido a partir del arreglo de bytes que contiene el archivo comprimido
    crearArchivoComprimido(arregloBytesArchivoComprimido);
    //creamos un archivo de texto con la tabla de frecuencias y los bytes cantidadbytes2
    crearArchivoTablaFrecuencias(argv[1], tablaFrecuencias);

    
    //tamano es la cantidad de bytes del archivo original
    //cantidadBytes2 es la cantidad de bytes del archivo comprimido


    //********************************************************************************************************************
    //EMPEZAR A DESCOMPRIMIR EL ARCHIVO
    //********************************************************************************************************************

    //abrir el archivo comprimido en modo lectura binaria
    FILE *archivoComprimido = fopen("archivoComprimido.dat", "rb");


    return 0;
}

//*******************Funciones del programa*******************


//funcion para crear una tabla de frecuencias de los bytes del archivo
//asigna a cada byte su frecuencia en el archivo

/*
DESCRIPCION DE LA FUNCION:
    Esta funcion recibe un arreglo de bytes y su tamaño y crea una tabla de frecuencias
    de los bytes del archivo. La tabla de frecuencias es un arreglo de 256 posiciones
    donde cada posicion representa un byte y su valor es la frecuencia de ese byte en el archivo.
    La funcion recorre el arreglo de bytes y por cada byte que encuentra aumenta en 1 la frecuencia
    de ese byte en la tabla de frecuencias.
ENTRADAS:
    unsigned char *bytes: arreglo de bytes del archivo
    int tamano: tamaño del archivo en bytes

SALIDAS:
    int *tablaFrecuencias: tabla de frecuencias de los bytes del archivo

*/
int *frecuencias(unsigned char *bytes, int tamano){

    //crear una tabla de frecuencias de los bytes del archivo
    int *tablaFrecuencias = malloc(256 * sizeof(int));
    for(int i = 0; i < 256; i++){
        tablaFrecuencias[i] = 0;
    }

    //recorrer el arreglo de bytes y por cada byte que encuentra aumenta en 1 la frecuencia de ese byte en la tabla de frecuencias
    for(int i = 0; i < tamano; i++){
        tablaFrecuencias[bytes[i]]++;
    }

    return tablaFrecuencias;
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
    de los bytes del archivo, donde cada hoja del arbol es un byte del archivo
    y la raiz es el nodo con la frecuencia total del archivo.
ENTRADA: 
   listaNodos: lista de nodos ordenada de menor a mayor frecuencia

SALIDA:
    raiz: puntero a la raiz del arbol de Huffman creado
*/
Nodo *crearArbolHuffman(Nodo *listaNodos){
    Nodo *nodoActual = listaNodos;
    Nodo *nodoNuevo = NULL;
    Nodo *nodoAuxiliar = NULL;

    //mientras la lista tenga mas de un nodo
    while(nodoActual->derecha != NULL){
        //crea un nuevo nodo con la suma de las frecuencias de los dos primeros nodos de la lista
        nodoNuevo = malloc(sizeof(Nodo));
        nodoNuevo->byte = 0;
        nodoNuevo->frecuencia = nodoActual->frecuencia + nodoActual->derecha->frecuencia;
        nodoNuevo->izquierda = nodoActual;
        nodoNuevo->derecha = nodoActual->derecha;
        nodoNuevo->codigo = NULL;

        //elimina los dos primeros nodos de la lista
        nodoActual = nodoActual->derecha->derecha;

        //inserta el nuevo nodo en la lista de manera ordenada de menor a mayor frecuencia
        if(nodoActual == NULL || nodoNuevo->frecuencia < nodoActual->frecuencia){
            nodoNuevo->derecha = nodoActual;
            nodoActual = nodoNuevo;
        }else{
            nodoAuxiliar = nodoActual;
            while(nodoAuxiliar->derecha != NULL && nodoAuxiliar->derecha->frecuencia <= nodoNuevo->frecuencia){
                nodoAuxiliar = nodoAuxiliar->derecha;
            }
            nodoNuevo->derecha = nodoAuxiliar->derecha;
            nodoAuxiliar->derecha = nodoNuevo;
        }
    }
    return nodoActual;
}



//funcion para crear una tabla de codigos de Huffman en binario a partir del arbol de Huffman 
//asigna a cada byte su codigo de Huffman en binario

/*
 DESCRIPCION DE LA FUNCION crearTablaCodigos: 
    Esta funcion crea una tabla de codigos de Huffman en binario a partir del arbol de Huffman 
    donde cada byte del archivo tiene su codigo de Huffman en binario

ENTRADA:
    raiz: puntero a la raiz del arbol de Huffman creado

SALIDA: 
    tablaCodigos: tabla de codigos de Huffman en binario
*/
char **crearTablaCodigos(Nodo *raiz){
    char **tablaCodigos = malloc(256 * sizeof(char*));
    char *codigo = malloc(256 * sizeof(char));
    for(int i = 0; i < 256; i++){
        tablaCodigos[i] = NULL;
    }
    crearTablaCodigosAux(raiz, tablaCodigos, codigo);
    return tablaCodigos;
}

//funcion auxiliar para crear una tabla de codigos de Huffman en binario a partir del arbol de Huffman
//asigna a cada byte su codigo de Huffman en binario
void crearTablaCodigosAux(Nodo *nodo, char **tablaCodigos, char *codigo){

    if(nodo->izquierda == NULL && nodo->derecha == NULL){
        tablaCodigos[nodo->byte] = malloc((strlen(codigo) + 1) * sizeof(char));
        strcpy(tablaCodigos[nodo->byte], codigo);
    }else{
        if(nodo->izquierda != NULL){
            codigo[strlen(codigo)] = '0';
            codigo[strlen(codigo) + 1] = '\0';
            crearTablaCodigosAux(nodo->izquierda, tablaCodigos, codigo);
            codigo[strlen(codigo) - 1] = '\0';
        }
        if(nodo->derecha != NULL){
            codigo[strlen(codigo)] = '1';
            codigo[strlen(codigo) + 1] = '\0';
            crearTablaCodigosAux(nodo->derecha, tablaCodigos, codigo);
            codigo[strlen(codigo) - 1] = '\0';
        }
    }
}

//funcion para crear un archivo de texto con la tabla de codigos de Huffman en binario
//asigna a cada byte su codigo de Huffman en binario
void crearArchivoTablaCodigos(char *nombreArchivo, char **tablaCodigos){

    FILE *archivo = fopen(nombreArchivo, "w");
    for(int i = 0; i < 256; i++){
        if(tablaCodigos[i] != NULL){
            fprintf(archivo, ".02X %s\n", i, tablaCodigos[i]);
        }
    }
    fclose(archivo);
}

//funcion para calcular la cantidad de bytes que ocupara el archivo comprimido ocupando el arreglo de frecuencias y la tabla de codigos
int calcularCantidadBytesArchivoComprimido(int *frecuencias, char **tablaCodigos){
    int cantidadBytes = 0;
    for(int i = 0; i < 256; i++){
        if(frecuencias[i] > 0){
            cantidadBytes += frecuencias[i] * strlen(tablaCodigos[i]);
        }
    }

    cantidadBytes2= cantidadBytes;

    if (cantidadBytes % 8 == 0){
        cantidadBytes = cantidadBytes / 8;
    }else{
        cantidadBytes = cantidadBytes / 8 + 1;
    }

    return cantidadBytes;
}

//funcion para crear el arreglo de bytes del archivo comprimido a partir de: la lectura del archivo original, la tabla de codigos de Huffman en binario y la cantidad de bytes que ocupara el archivo comprimido
char *crearArregloBytesArchivoComprimido(char *nombreArchivo, char **tablaCodigos, int cantidadBytesArchivoComprimido){
    char *arregloBytesArchivoComprimido = malloc(cantidadBytesArchivoComprimido * sizeof(char));
    char *codigo = malloc(256 * sizeof(char));
    char *byte = malloc(9 * sizeof(char));
    int indiceArregloBytesArchivoComprimido = 0;
    int indiceByte = 0;
    int indiceCodigo = 0;
    int byteActual = 0;
    int cantidadBytesArchivoOriginal = 0;
    int cantidadBitsUltimoByte = 0;

    FILE *archivo = fopen(nombreArchivo, "r");
    fseek(archivo, 0, SEEK_END);
    cantidadBytesArchivoOriginal = ftell(archivo);
    fseek(archivo, 0, SEEK_SET);

    for(int i = 0; i < cantidadBytesArchivoOriginal; i++){
        byteActual = fgetc(archivo);
        strcpy(codigo, tablaCodigos[byteActual]);
        for(int j = 0; j < strlen(codigo); j++){
            byte[indiceByte] = codigo[j];
            indiceByte++;
            if(indiceByte == 8){
                byte[indiceByte] = '\0';
                arregloBytesArchivoComprimido[indiceArregloBytesArchivoComprimido] = strtol(byte, NULL, 2);
                indiceArregloBytesArchivoComprimido++;
                indiceByte = 0;
            }
        }
    }

    if(indiceByte > 0){
        cantidadBitsUltimoByte = indiceByte;
        for(int i = 0; i < 8 - cantidadBitsUltimoByte; i++){
            byte[indiceByte] = '0';
            indiceByte++;
        }
        byte[indiceByte] = '\0';
        arregloBytesArchivoComprimido[indiceArregloBytesArchivoComprimido] = strtol(byte, NULL, 2);
        indiceArregloBytesArchivoComprimido++;
    }

    arregloBytesArchivoComprimido[indiceArregloBytesArchivoComprimido] = '\0';
    fclose(archivo);
    return arregloBytesArchivoComprimido;
}


//funcion para crear el archivo comprimido a partir del arreglo de bytes del archivo comprimido
void crearArchivoComprimido(char *arregloBytesArchivoComprimido){
    FILE *archivo = fopen("archivoComprimido.dat", "wb");
    fwrite(arregloBytesArchivoComprimido, sizeof(char), strlen(arregloBytesArchivoComprimido), archivo);
    fclose(archivo);
}

//funcion para crear el archivo de texto con la tabla de frecuencias a partir del:
// arreglo de frecuencias, la cantidad de bits del archivo comprimido y la cantidad de bytes del archivo original
void crearArchivoTablaFrecuencias(char *nombreArchivo, int *frecuencias){

    FILE *archivo = fopen(nombreArchivo, "w");

    for(int i = 0; i < 256; i++){
        if(frecuencias[i] > 0){
            fprintf(archivo, ".02X %d\n", i, frecuencias[i]);
        }
    }
}

//**********************************************************************************************************************
//funciones para descomprimir un archivo comprimido
//**********************************************************************************************************************
//funcion para descomprimir un archivo comprimido
void descomprimirArchivo(char *nombreArchivo){

    int *frecuencias = NULL;
    int cantidadBytesArchivoComprimido = 0;
    char *arregloBytesArchivoComprimido = NULL;
    Nodo *raiz = NULL;
    char **tablaCodigos = NULL;
    char *arregloBytesArchivoDescomprimido = NULL;

    frecuencias = leerArchivoTablaFrecuencias(nombreArchivo);
    cantidadBytesArchivoComprimido = leerCantidadBytesArchivoComprimido(nombreArchivo);
    arregloBytesArchivoComprimido = leerArregloBytesArchivoComprimido(nombreArchivo, cantidadBytesArchivoComprimido);
    raiz = crearArbolHuffman(frecuencias);
    tablaCodigos = crearTablaCodigos(raiz);
    arregloBytesArchivoDescomprimido = crearArregloBytesArchivoDescomprimido(arregloBytesArchivoComprimido, tablaCodigos, cantidadBytesArchivoComprimido);
    crearArchivoDescomprimido(arregloBytesArchivoDescomprimido);

    free(frecuencias);
    free(arregloBytesArchivoComprimido);
    free(arregloBytesArchivoDescomprimido);
    liberarArbolHuffman(raiz);
    liberarTablaCodigos(tablaCodigos);
}

//funcion de crear archivo descomprimido
void crearArchivoDescomprimido(char *arregloBytesArchivoDescomprimido){
    FILE *archivo = fopen("archivoDescomprimido.txt", "w");
    fprintf(archivo, "%s", arregloBytesArchivoDescomprimido);
    fclose(archivo);
}
