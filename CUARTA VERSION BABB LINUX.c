/*
 *	AN�LISIS Y DISE�O DE ALGORITMOS
 *
 *	PR�CTICA 02: Implementaci�n de la b�squeda en ABB, utilizando el c�digo proporcionado de GeeksForGeeks.
 *	https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/ 
 * -------------------
 *	EQUIPO: LOS B�LICOS
 * 
 *	VERSION DE CODIGO: 5.0
 * 
 *	FECHA: 2/05/2023
 *
 *	REALIZ�: MEDINA ZEPEDA SAMANTHA
 *
 *
 */
 
//ejecutar en terminal: ./scriptBABB1.sh n n1 n2 n3
//ejemplo: ./scriptBABB1.sh 4 10000000 6 20

//Declaraci�n de librer�as
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "recursos/tiempo.h"

/*Declramos la estructura del nodo con los siguientes elementos:

	dato, hijo izquierdo y derecho, �ndice que nos indicar� la posici�n del n�mero.
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
	int i, p;
	int n,*A,val;
	//int num;
	//int *numeros_a_buscar,*A, *tamano;
	//int i,j,k;
	Nodo* raiz = NULL;
    Nodo* ind = NULL;
    
    double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medici?n de tiempos
	//double utime02, stime02, wtime02,utime12, stime12, wtime12;
	
	if(argc != 2)
	{
		printf("\n\n Para ejecutar el programa se necesita tama�o de arreglo");
		//printf("\n Ejemplo: %s 100", argv[0]);
		exit(1);
	}
	
    n = atoi(argv[1]);
    val = atoi(argv[2]);
    A = (int*) malloc(n * sizeof(int));
	
		scanf("%d", &A[0]);
	raiz= Insertar(raiz, A[0],0);

	for(i=0; i<n; i++)
	{
		scanf("%d", &A[i]);
		Insertar(raiz, A[i],i);
	}
	
	printf("\n---------------------Implementacion sin hilos---------------------\n\n");
	
	ind = Buscar(raiz, val); 	
   	if (ind)
    {
    	printf("Numero Encontrado=%d\n", ind->dato);
   	}
    else
    {
    	printf("Lo sentimos, no se encontro el numero.\n");
    }
    
    printf("\n\n");

		printf("\nTiempo de ejecucion del programa\n");
		printf("real (Tiempo total):  %.10f s\n",  (wtime12 - wtime02)/20);
		printf("user (Tiempo de procesamiento en CPU): %.10f s\n",  (utime12 - utime02)/20);
		printf("sys (Tiempo en acci�nes de E/S):  %.10f s\n",  (stime12 - stime02)/20);
		printf("CPU/Wall:   %.10f %% \n",100.0 * ((utime12 - utime02 + stime12 - stime02) / (wtime12 -wtime02))/20);
		printf("\n");
		
		//Mostrar los tiempos en formato exponecial
		printf("\nFormato exponencial\n");
		printf("real (Tiempo total):  %.10e s\n",  (wtime12 - wtime02)/20);
		printf("user (Tiempo de procesamiento en CPU): %.10e s\n",  (utime12 - utime02)/20);
		printf("sys (Tiempo en acci�nes de E/S):  %.10e s\n",  (stime12 - stime02)/20);
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

	�Qu� par�metros recibe? 
		item : valor que estar� en el nodo
		indice : posici�n de dicho valor en el arreglo
La funci�n crea un nodo con el item que le mandamos, reserva la memoria, asigna el item al dato, e inicializa los apuntadores del hijo izquierdo y derecho en NULL
�Qu� regresa?
- El nuevo nodo (su direcci�n)
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

	�Qu� par�metros recibe? 
		*Nodo : direcci�n del nodo
		val : valor que tendr� el nodo
		indice : su posici�n
La funci�n inserta elementos en el �rbol, siguiendo la forma adecuada de hacerlo en la b�squeda con ABB (que se explica m�s abajo)
�Qu� regresa?
- Hay dos opciones, si el �rbol estaba vac�o regresa la direcci�n del nodo, si no, regresa el apuntador de Nodo
*/
Nodo* Insertar(Nodo* Nodo, int val, int indice)
{
	/* CASO EN EL QUE EL �RBOL EST� VAC�O */
	if (Nodo == NULL) // sabe que est� vac�o porque se cumple que Nodo es igual con NULL
		return NuevoNodo(val, indice); //Llama a la funci�n NuevoNodo y lo crea

	/* CASO EN EL QUE YA HAY ELEMENTOS
		En una b�squeda con ABB los elementos menores al dato de la ra�z se insertan en el hijo izquierdo y los mayores se insertan en el hijo derecho
	 */
	if (val < Nodo->dato)
		Nodo->izq = Insertar(Nodo->izq, val, indice);
	else if (val > Nodo->dato)
		Nodo->der = Insertar(Nodo->der, val, indice);
	return Nodo;
}

/*	Nodo* Buscar(Nodo* raiz, int val)

	�Qu� par�metros recibe? 
		*raiz : direcci�n del nodo raiz
		val : valor que tiene el nodo
La funci�n busca elementos en el �rbol, y lo hace siguiendo la forma de b�squeda con ABB (como en la funci�n insertar)
�Qu� regresa?
- Regresa la direcci�n del nodo raiz
*/
Nodo* Buscar(Nodo* raiz, int val)
{
	// CASO BASE: raiz es igual con NULL o el n�mero a buscar est� en el nodo raiz
	if (raiz == NULL || raiz->dato == val)
	return raiz;
	
	// CASO 1: El valor a buscar es mayor que el dato de la raiz
	if (raiz->dato < val)
	return Buscar(raiz->der, val);

	// CASO 2: El valor a buscar es menor que el dato de la raiz
	return Buscar(raiz->izq, val);
}

/*	void InOrden(Nodo* raiz)

	�Qu� par�metros recibe? 
		*raiz : El nodo raiz del arbol (su direcci�n)
La funci�n imprime los valores utilizando Inorden, de tal forma que los elementos se imprimen ordenados
�Qu� regresa?
- En este caso solo nos imprime los valores, la funci�n en si es de tipo void.
*/
void InOrden(Nodo* raiz)
{
	if (raiz != NULL) {
		InOrden(raiz->izq);
		printf("%d \n", raiz->dato);
		InOrden(raiz->der);
	}
}
