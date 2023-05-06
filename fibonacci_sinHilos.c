

/*
 * ANALISIS Y DISENO DE ALGORITMOS
 *
 *ALGORITMO HEAPSORT DE LA PRACTICA 1: IMPLEMENTACION Y ANALISIS DE EJECUCION DEL ALGORITMO FUBONACCI SIN HILOS.
 * -------------------
 * EQUIPO: LOS BELICOS
 * 
 * VERSION DE CODIGO: 12.0
 * 
 *FECHA: 15/04/2023
 *
 *REALIZO: TORRES GUZMAN CESAR HAVIT
 *
 *
 */


//ejecutar en terminal: ./scriptFibonacci1.sh n n1 n2 n3
//ejemplo: ./scriptFibonacci1.sh 4 10000000 6 20

#include <stdio.h>
#include <stdlib.h>
#include "recursos/tiempo.h"

int min(int x, int y);
int fibMonaccianSearch(int *a, int x, int n);


int main(int arg, char* argv[])
{
	int num;
	int *numeros_a_buscar,*A, *tamano; //Arreglo de numeros a buscar y arreglo de tama�os
	int i,j,k;
	double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medici�n de tiempos
	double utime02, stime02, wtime02,utime12, stime12, wtime12;

	//******************************************************************
	//variables para leer archivos
    int n, n2,n3,ind;
    FILE *fp1, *fp2,*fp3;
	//******************************************************************

	//leyendo argumentos y generando espacio para los arreglos
	
    n = atoi(argv[1]);
    A = (int*) malloc(n * sizeof(int));

   	n2  = atoi(argv[2]);
    tamano = (int*) malloc(n2 * sizeof(int));

    n3 = atoi(argv[3]);
    numeros_a_buscar = (int*) malloc(n3 * sizeof(int));


	//abriendo archivos

    fp1 = fopen(argv[4], "r");
    fp2 = fopen(argv[5], "r");
	fp3 = fopen(argv[6], "r");


	//revisando que los archivos se hayan abierto correctamente
    if (fp1 == NULL || fp2 == NULL || fp3 == NULL) {
        printf("Error al abrir los archivos de texto.\n");
        exit(1);
    }

	//leyendo los archivos y guardando los datos en los arreglos
    for (i = 0; i < n; i++) {
        fscanf(fp1, "%d", &A[i]);
    }

	for (i = 0; i < n2; i++) {
        fscanf(fp2, "%d", &tamano[i]);
    }

    for (i = 0; i < n3; i++) {
        fscanf(fp3, "%d", &numeros_a_buscar[i]);
    }


    //cerrando archivos
    fclose(fp1);
    fclose(fp2);
	fclose(fp3);
	//******************************************************************

	printf("\n---------------------Implementacion sin hilos---------------------\n\n");

	// en n2 se guardan los tama�os de los arreglos, por eso se usa para el ciclo
	for( i = 0; i < n2; i++)
	{
		printf("\n\npara n: %d\n\n",tamano[i]);
		//en n3 se guardan los numeros a buscar, por eso se usa para el ciclo
		for (j = 0; j < n3 ;j++) {

			num= numeros_a_buscar[j];

			printf("\n\n-----> Buscando %d\n", num);


			uswtime(&utime0, &stime0, &wtime0);
			ind = fibMonaccianSearch(A, num, n);
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
				

			//Imprimir el numero si se encontro o no, yo no lo imprimo porque llena el archivo de texto de datos

			/*
			if(ind >= 0)
				printf("\n\nnumero encontrado en el lugar: %d\n\n",ind);
			else
				printf("\n\nel numero %d no se encuentra en el arreglo\n\n ",num);
			*/
	
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

	}
	



		
	free(A);
	return 0;

}



/*
DESCRIPCION:La funcion min encuentra el minimo entre dos numeros. 
PARAMETRO x: Numero a comparar.
PARAMETRO y: numero a comparar.

RETORNO:Retorna el numero mas peque�o entre los 2.
*/

int min(int x, int y)
{ return (x <= y) ? x : y; }


/*
DESCRIPCION:La funcion fibMonaccianSearch es una busqueda de fibonacci.
PARAMETRO a: Arreglo donde se va a buscar.
PARAMETRO x: Numero a buscar.
PARAMETRO n: Tama�o del arreglo.
*/

/* Returns index of x if present, else returns -1 */
int fibMonaccianSearch(int *a, int x, int n)
{
	/* Initialize fibonacci numbers */
	int fibMMm2 = 0; // (m-2)'th Fibonacci No.
	int fibMMm1 = 1; // (m-1)'th Fibonacci No.
	int fibM = fibMMm2 + fibMMm1; // m'th Fibonacci

	/* fibM is going to store the smallest Fibonacci
	Number greater than or equal to n */
	while (fibM < n) {
		fibMMm2 = fibMMm1;
		fibMMm1 = fibM;
		fibM = fibMMm2 + fibMMm1;
	}

	// Marks the eliminated range from front
	int offset = -1;

	/* while there are elements to be inspected. Note that
	we compare arr[fibMm2] with x. When fibM becomes 1,
	fibMm2 becomes 0 */
	while (fibM > 1) {
		// Check if fibMm2 is a valid location
		int i = min(offset + fibMMm2, n - 1);

		/* If x is greater than the value at index fibMm2,
		cut the subarray array from offset to i */
		if (a[i] < x) {
			fibM = fibMMm1;
			fibMMm1 = fibMMm2;
			fibMMm2 = fibM - fibMMm1;
			offset = i;
		}

		/* If x is greater than the value at index fibMm2,
		cut the subarray after i+1 */
		else if (a[i] > x) {
			fibM = fibMMm2;
			fibMMm1 = fibMMm1 - fibMMm2;
			fibMMm2 = fibM - fibMMm1;
		}

		/* element found. return index */
		else
			return i;
	}

	/* comparing the last element with x */
	if (fibMMm1 && a[offset + 1] == x)
		return offset + 1;

	/*element not found. return -1 */
	return -1;
}
