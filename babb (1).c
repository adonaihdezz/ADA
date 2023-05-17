/*
 *	ANÁLISIS Y DISEÑO DE ALGORITMOS
 *
 *	PRÁCTICA 02: Implementación de la búsqueda en ABB, utilizando el código proporcionado de GeeksForGeeks.
 *	https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/ 
 * -------------------
 *	EQUIPO: LOS BÉLICOS
 * 
 *	VERSION DE CODIGO: 5.0
 * 
 *	FECHA: 2/05/2023
 *
 *	REALIZÓ: MEDINA ZEPEDA SAMANTHA
 *
 *
 */
 
//ejecutar en terminal: ./scriptBABB1.sh n n1 n2 n3
//ejemplo: ./scriptBABB1.sh 4 10000000 6 20

// ./babb N val > babb_salida.txt < numeros.txt    // Asi se ejecuta en la terminal
// gcc babb.c -o babb tiempos/tiempo.c		 // Asi se compila

//Declaración de librerías
#include <stdio.h>
#include <stdlib.h>
#include "tiempos/tiempo.h"

/*Declramos la estructura del nodo con los siguientes elementos:

	dato, hijo izquierdo y derecho, índice que nos indicará la posición del número.
*/
typedef struct Nodo 
{
	int dato;
	struct Nodo *izq, *der;
	int indice;
}Nodo;

//Funciones utilizadas

Nodo* NuevoNodo(int item, int indice);
Nodo* Insertar(Nodo* Nodo, int val, int indice);
Nodo* Buscar(Nodo* raiz, int val);
void InOrden(Nodo* raiz);

int main(int argc, char *argv[])
{
	long int numeros_a_buscar[] = {322486, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644, 1295390003, 450057883, 187645041, 1980098116, 152503, 5000, 1493283650, 214826, 18433949527, 1360839354, 2109248666, 2147470852, 0};
	
	//1698402220 fake
	//322486
	// 2147445644
    int num_numeros_a_buscar = sizeof(numeros_a_buscar) / sizeof(numeros_a_buscar[0]);
	int i, p, j, k;
	int n,val;
	int *A, *tamano;
	Nodo* raiz = NULL;
 	Nodo* ind = NULL;
    
    double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medicion de tiempos
    double utime02, stime02, wtime02,utime12, stime12, wtime12;
    
	
	if(argc != 2)
	{
		printf("\n\n Para ejecutar el programa se necesita tamaño de arreglo");
		printf("\n Ejemplo: %s 100", argv[0]);
		exit(1);
	}
	
    n = atoi(argv[1]);
    //val = atoi(argv[2]);
    A = (int*) malloc(n * sizeof(int));
    
    
    //INSERTO LOS ELEMENTOS EN EL ARREGLO
		scanf("%d", &A[0]);
	raiz= Insertar(raiz, A[0],0);

	for(i=1; i<n; i++)
	{
		scanf("%d", &A[i]);
		Insertar(raiz, A[i],i);
	}
	
	
// en n2 se guardan los tamanos de los arreglos, por eso se usa para el ciclo
	for( i = 0; i < num_numeros_a_buscar; i++)
	{
		val= numeros_a_buscar[i];
		printf("\n\npara n: %d\n\n",n);
			printf("\n\n-----> Buscando %d\n", val);


			uswtime(&utime0, &stime0, &wtime0);
			ind = Buscar(raiz, val); 
			uswtime(&utime1, &stime1, &wtime1);

			utime02+=utime0;
			stime02+=stime0;
			wtime02+=wtime0;
			utime12+=utime1;
			stime12+=stime1;
			wtime12+=wtime1;

			utime0=0;
			stime0=0;
			wtime0=0;
			utime1=0;
			stime1=0;
			wtime1=0;
				

		if (ind != NULL)
		    {
		    	printf("Numero Encontrado=%d\n", ind->indice);
		    }
		else
		    {
		    	printf("Lo sentimos, no se encontro el numero.\n");
		    }
		    
		    printf("\n\n");
	
		}	

		//printf("\n\n");

		printf("\nTiempo de ejecucion del programa\n");
		printf("real (Tiempo total):  %.10f s\n",  (wtime12 - wtime02)/20);
		printf("user (Tiempo de procesamiento en CPU): %.10f s\n",  (utime12 - utime02)/20);
		printf("sys (Tiempo en acciónes de E/S):  %.10f s\n",  (stime12 - stime02)/20);
		printf("CPU/Wall:   %.10f %% \n",100.0 * ((utime12 - utime02 + stime12 - stime02) / (wtime12 -wtime02))/20);
		printf("\n");
		
		//Mostrar los tiempos en formato exponecial
		printf("\nFormato exponencial\n");
		printf("real (Tiempo total):  %.10e s\n",  (wtime12 - wtime02)/20);
		printf("user (Tiempo de procesamiento en CPU): %.10e s\n",  (utime12 - utime02)/20);
		printf("sys (Tiempo en acciónes de E/S):  %.10e s\n",  (stime12 - stime02)/20);
		printf("CPU/Wall:   %.10f %% \n",100.0 * ((utime12 - utime02 + stime12 - stime02) / (wtime12 - wtime02))/20);
		printf("\n");
		printf("\n\n**************************************\n\n");


		//Liberamos la memoria
    free(raiz);
	raiz = NULL;
	free(A);

	return 0;	
}

/*	Nodo* NuevoNodo(int item, int indice)

	¿Qué parámetros recibe? 
		item : valor que estará en el nodo
		indice : posición de dicho valor en el arreglo
La función crea un nodo con el item que le mandamos, reserva la memoria, asigna el item al dato, e inicializa los apuntadores del hijo izquierdo y derecho en NULL
¿Qué regresa?
- El nuevo nodo (su dirección)
*/
Nodo* NuevoNodo(int item, int indice)
{
	Nodo* temp	= (Nodo*)malloc(sizeof(struct Nodo));
	temp->dato = item;
	temp->izq = temp->der = NULL;
	temp->indice = indice;
	return temp;
}

/*	Nodo* Insertar(Nodo* Nodo, int val, int indice)

	¿Qué parámetros recibe? 
		*Nodo : dirección del nodo
		val : valor que tendrá el nodo
		indice : su posición
La función inserta elementos en el árbol, siguiendo la forma adecuada de hacerlo en la búsqueda con ABB (que se explica más abajo)
¿Qué regresa?
- Hay dos opciones, si el árbol estaba vacío regresa la dirección del nodo, si no, regresa el apuntador de Nodo
*/
Nodo* Insertar(Nodo* Nodo, int val, int indice)
{
	/* CASO EN EL QUE EL ÁRBOL ESTÁ VACÍO */
	if (Nodo == NULL) // sabe que está vacío porque se cumple que Nodo es igual con NULL
		return NuevoNodo(val, indice); //Llama a la función NuevoNodo y lo crea

	/* CASO EN EL QUE YA HAY ELEMENTOS
		En una búsqueda con ABB los elementos menores al dato de la raíz se insertan en el hijo izquierdo y los mayores se insertan en el hijo derecho
	 */
	if (val < Nodo->dato)
		Nodo->izq = Insertar(Nodo->izq, val, indice);
	else if (val > Nodo->dato)
		Nodo->der = Insertar(Nodo->der, val, indice);
	return Nodo;
}

/*	Nodo* Buscar(Nodo* raiz, int val)

	¿Qué parámetros recibe? 
		*raiz : dirección del nodo raiz
		val : valor que tiene el nodo
La función busca elementos en el árbol, y lo hace siguiendo la forma de búsqueda con ABB (como en la función insertar)
¿Qué regresa?
- Regresa la dirección del nodo raiz
*/
Nodo* Buscar(Nodo* raiz, int val)
{
	// CASO BASE: raiz es igual con NULL o el número a buscar está en el nodo raiz
	if (raiz == NULL || raiz->dato == val)
	return raiz;
	
	// CASO 1: El valor a buscar es mayor que el dato de la raiz
	if (raiz->dato < val)
	return Buscar(raiz->der, val);

	// CASO 2: El valor a buscar es menor que el dato de la raiz
	return Buscar(raiz->izq, val);
}

/*	void InOrden(Nodo* raiz)

	¿Qué parámetros recibe? 
		*raiz : El nodo raiz del arbol (su dirección)
La función imprime los valores utilizando Inorden, de tal forma que los elementos se imprimen ordenados
¿Qué regresa?
- En este caso solo nos imprime los valores, la función en si es de tipo void.
*/
void InOrden(Nodo* raiz)
{
	if (raiz != NULL) {
		InOrden(raiz->izq);
		printf("%d \n", raiz->dato);
		InOrden(raiz->der);
	}
}
