//ARBOL BINARIO CON HILOS PRIMER INTENTO 
/*
 *	ANÁLISIS Y DISEÑO DE ALGORITMOS
 *
 *	PRÁCTICA 02: Implementación de la búsqueda en ABB CON HILOS, utilizando el código proporcionado de GeeksForGeeks.
 *	https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/ 
 * -------------------
 *	EQUIPO: LOS BÉLICOS
 * 
 *	VERSION DE CODIGO: 2.0
 * 
 *	FECHA: 07/05/2023
 *
 *	REALIZÓ: MEDINA ZEPEDA SAMANTHA
 *
 *
 */
 
//ejecutar en terminal: ./scriptBABB1.sh n n1 n2 n3
//ejemplo: ./scriptBABB1.sh 4 10000000 6 20

// ./babbh 1000000 4 > babbh_salida.txt < numeros.txt   // Asi se ejecuta en la terminal
// gcc babbh.c -o babbh tiempos/tiempo.c  -lm		 // Asi se compila

//Declaración de librerías
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "tiempos/tiempo.h"


/*Declaramos la estructura del nodo con los siguientes elementos:

	dato, hijo izquierdo y derecho, índice que nos indicará la posición del número.
*/
typedef struct Nodo 
{
	int dato;
	struct Nodo *izq, *der;
	int indice;
}Nodo;

//VARIABLES GLOBALES
//*****************************************************************
int NumThreads;				// Número de threads
int N;						// Tamaño del arreglo
int val;						// Variable a encontrar en el arreglo
int *A;						// Apuntador al arreglo
int p;						// Variable para guardar el indice
Nodo *raiz = NULL;		// Apuntador a la raiz del arbol
int **B = NULL;				// Apuntador a la matriz para los hilos
int k, c;	

//Funciones utilizadas

Nodo* NuevoNodo(int item, int indice);
Nodo* Insertar(Nodo* Nodo, int val, int indice);
Nodo* Buscar(Nodo* raiz, int val);
void InOrden(Nodo* raiz);
void* procesar(void* id);

int main(int argc, char *argv[])
{
	long int numeros_a_buscar[] = {322486, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644, 1295390003, 450057883, 187645041, 1980098116, 152503, 5000, 1493283650, 214826, 18433949527, 1360839354, 2109248666, 2147470852, 0};
	
	//1698402220 fake
	//322486
	// 2147445644
    int num_numeros_a_buscar = sizeof(numeros_a_buscar) / sizeof(numeros_a_buscar[0]);
	pthread_t *thread;
	int i, j, l;
	int m, n, d;
	//int num;

    //Nodo* ind = NULL;
    
    double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medicion de tiempos
    double utime02, stime02, wtime02,utime12, stime12, wtime12;
	
	if(argc != 3)
	{
		printf("\n\n Para ejecutar el programa se necesita tamaño de arreglo");
		//printf("\n Ejemplo: %s 100", argv[0]);
		exit(1);
	}
	
    N = atoi(argv[1]);
    A = (int*) malloc(n * sizeof(int));
    NumThreads = atoi(argv[2]);
	thread = malloc(NumThreads*sizeof(pthread_t));
	// Se da el valor inicial de -1 a p
	p = -1;
    
    //val = atoi(argv[2]);
    
	
		scanf("%d", &A[0]);
	raiz= Insertar(raiz, A[0],0);

	for(i=1; i<n; i++)
	{
		scanf("%d", &A[i]);
		Insertar(raiz, A[i],i);
	}
	
	
	printf("\n\n    BÚSQUEDA CON ÁRBOL BINARIO\n    con %d números y %d hilos", N, NumThreads);
	
	/*EXPLICACIÓN DE LOS HILOS*/

for(i=0; NumThreads>=pow(2,i); i++);			// (Solo se ejecuta lo del parentesis)

	k = i;											// Se define el valor de k
	c = pow(2,k)-NumThreads;						//NumThreads=2^k-c   ---- Ecuación para obtener C despejando

	// CREACIÓN DE LA MATRIZ PARA LOS HILOS (tabla de combinaciones)
		/*Matriz con base en d, k y l (Utlizando memoria dinámica)
		En donde k: número de filas
				 d: variable auxiliar para llenar TODA la columna
				 l: variable auxiliar para llenar un conjunto de 0...1...
			Por ejemplo, si se tiene una matriz que 2^k filas y k columnas
			Para llenar la primera columna, el número de valores unos o ceros consecutivos es d=2^(k-1)
			En el mismo ejemplo, al llenar la columna 2, d=2^(k-2)
			De manera generalizada d=2^(k-1-j) para 0<=j<n
		*/
	m = pow(2,k);												// Número de filas
	n = k;														// Número de columnas
	B = (int **)malloc(m*sizeof(int*)); 						// Memoria para el numero de filas
	//Tamaño a las filas (numero de columnas)
	for(i=0; i<m; i++){
		B[i] = (int*)malloc(n*sizeof(int));
	}
	// Asignacion de los valores de la tabla de combinaciones
	for(j=0; j<n; j++){
		d = pow(2, k-1-j);
		for(i=0; i<m; i+=2*d){				//Salto de 2*d porque ya se llenaron los unos
			for(l=i; l<d+i; l++){
				B[l][j] = 0;				// Asigna los ceros
				B[l+d][j] = 1;				// Asigna los unos consecutivos a los ceros
			}
		}
	}

	
	// Ejecución del algoritmo de búsqueda
	for(j = 1; j <= num_numeros_a_buscar ; j++){
	
		val= numeros_a_buscar[j];
		//v = Element(&mi_cola, j).n;
		p = -1;
		printf("\n\n Valor a encontrar: %d", val);

		// Inicia la medición de tiempos
		uswtime(&utime0, &stime0, &wtime0);
		//Crear los threads con el comportamiento "segmentar"
		for (i=1; i<NumThreads; i++) 
		{
			//En esta parte es cuando se realiza la búsqueda en los threads 1, ..., a_NumThreads
			if (pthread_create (&thread[i], NULL, procesar,(void*)i) != 0 ) 
			{
				perror("El thread no pudo crearse");
				exit(-1);
			}
		}

		//El main ejecuta el thread 0
		procesar(0);
		//Esperar a que terminen los threads (procesar)
		for (i=1; i<NumThreads; i++){
			pthread_join (thread[i], NULL);}

		// Termina la medición de tiempos
		uswtime(&utime1, &stime1, &wtime1);

		// /*											Comentar si no se quiere imprimir la posición en donde se encontró
		//Se imprime la posición del arreglo en la que se encontró o, en su defecto, -1 si no se encuentra en arreglo
		if(p == -1){
			printf("\n \033[91mNO SE ENCONTRÓ EL NÚMERO\033[0m");
		}
		else{
			printf("\n \033[92mSe encontró en la posición:\033[0m %d", p);
		}
		
		//rendimiento(utime0, stime0, wtime0, utime1, stime1, wtime1);
		
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
	}
	
	printf("\n\n");

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

	//Libera la memoria de los arreglos y del arbol
	free(raiz);
	raiz = NULL;
	free(A);
	for(i=0; i<n; i++ ){
	free(B[i]);
	}
	free(B);
	
	return 0;
	
}	
	
	
	
	
	
	
	
	
	
	/*printf("\n---------------------Implementacion sin hilos---------------------\n\n");
	uswtime(&utime0, &stime0, &wtime0); 
	
	ind = Buscar(raiz, val); 	
   	if (ind != NULL)
    {
    	printf("Numero Encontrado=%d\n", ind->indice);
   	}
    else
    {
    	printf("Lo sentimos, no se encontro el numero.\n");
    }
    
    printf("\n\n");

		//Cálculo del tiempo de ejecución del programa
	printf("\n");
	printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10f s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 -wtime0));
	printf("\n");
	
	//Mostrar los tiempos en formato exponecial
	printf("\n");
	printf("real (Tiempo total)  %.10e s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10e s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	
	printf("******************************************************************");
    printf("\n");
		
		//Liberamos la memoria
    free(raiz);
	raiz = NULL;
	free(A);

	return 0;	
}*/

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

/*EXPLICACIÒN VOID PROCESAR*/

/*
void* procesar(void* id)
Recibe:	id:	id del thread
Hace los calculos necesarios para seleccionar el nodoC raiz del subárbol en donde
trabajará el hilo seleccionado e imprime el mensaje de la utilización del hilo.
Finalmente, hace la búsqueda y actualiza el valor de p solo si se encontró el
elemento en dicho intervalo.
*/
void* procesar(void* id)
{	
	int n_thread=(int)id;						// Número de hilo
	int fila;									// Fila de la combinación correspondiente al hilo
	int i, j;									// Variables contadoras
	int noprocesar = 0;							// Dentiene la búsqueda si se encuentra el valor o aux apunta a NULL
	// Apuntador para guardar el nodoC en donde se encontró el valor
	struct Nodo *encontrado = NULL;
	//Apuntador auxiliar para iniciar la busqueda
	struct Nodo *aux = raiz;

	//Revisar la parte de los datos a procesar	
	if(n_thread<(pow(2,k)-2*c)){
		i = 0;									// Si es del nivel k, se toman todos los valores de la combinación
		fila = n_thread;
	}
	else{
		i = 1;									// Si es del nivel k-1, no se toma el último valor de la combinación
		fila = 2*n_thread - (pow(2,k)-2*c);					// Cálculo de la fila (se toma la primera)
	}
		
	//Ciclo para recorrer el árbol y posicionarse en el nodoC en donde se iniciará la búsqueda
	for(j=0; j<k-i; j++){
		// Caso donde no hay valores en el subárbol
		if(aux==NULL){
			noprocesar = 1;									// Indica que no se realizará la búsqueda
			break;
		}
		// Caso donde si hay valores en el subárbol
		if(aux!=NULL){
			//Caso donde el valor se encontró en el proceso
			if(aux->dato==val){
				encontrado = aux;							//Asigna el valor en donde se encontró
				noprocesar = 1;								// Indica que no se realizará la búsqueda
				break;
			}
			// Caso elegir hijo izquierdo
			if(B[fila][j]==0){
				aux=aux->izq;
			}
			// Caso elegir hijo derecho
			else{
				aux=aux->der;
			}
		}
	}

	// Caso en donde se indicó que se debía procesar
	if(noprocesar==0){
		//printf("\nHola desde procesar\tSoy el thread %d\t He comenzado",n_thread);	//Comentar para la información del hilo
		// Ejecución del algoritmo de búsqueda, se le da un valor entero a "p" (para el resultado final) con base en el resultado de la búsqueda
		encontrado = Buscar(aux, val);
		// Caso en el que si se encontró
		if(encontrado != NULL){
			p = encontrado->indice;
			//printf("\n Encontrado en el thread %d, %d", n_thread, p);									//Comentar para no mostrar el índice.
		}
		
		//printf("\nBye desde procesar\tSoy el thread %d\t He terminado",n_thread);	//Comentar para no mostrar
	}
	// Caso en donde se indicó que no se debía procesar
	else{
		//printf("\nHola desde procesar\tSoy el thread %d NO ME TOCÓ PROCESAR DATOS",n_thread);	//Comentar que no se procesará en ese hilo
		if(encontrado!=NULL){
			p = encontrado->indice;
		}
		//printf("\nBye desde procesar\tSoy el thread %d\t He terminado",n_thread);	//Comentar para no mostrar
	}
}
