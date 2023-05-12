/*
Analisis y diseno de algoritmos 

Equipo: Los belicos 

Version del codigo: 10

Fecha: 05/05/2023

Realizo: Jesus Adonai Perez Hernandez

*/
//Ejecutar en terminal: 
// Ejemplo 

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "recursos/tiempo.h"

//Variables globales y funciones 

int NumThreads;
int N, *A, num, n, ind = -1;

int busquedalineal(int *a, int x, int inicio, int fin);
void *procesar(void *id);

int main(int arg, char *argv[])
{

	long int numeros_a_buscar[] = {322486, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644, 1295390003, 450057883, 187645041, 1980098116, 152503, 5000, 1493283650, 214826, 18433949527, 1360839354, 2109248666, 2147470852, 0};
	int num_numeros_a_buscar = sizeof(numeros_a_buscar) / sizeof(numeros_a_buscar[0]);
	
	int i, j, k, tmp;
	
	double utime0, stime0, wtime0, utime1, stime1, wtime1;
	double utime02, stime02, wtime02,utime12, stime12, wtime12;
	

	pthread_t *thread;
//Verificar parametros y llenado del arreglo 

    if (arg < 2)
	{
		printf("Indique el numero de threads %s\n", argv[0]);
		exit(-1);
	}
	NumThreads = atoi(argv[1]);
	thread = malloc(NumThreads * sizeof(pthread_t));


	if (arg != 3)
	{
		printf("Ingrese tamano del arreglo y numero a buscar\n");
		exit(1);
	}


	n = atoi(argv[2]);
	A = (int *)malloc(n * sizeof(int));

    printf("para n: %d\n", n);

    for (i = 0; i < n; i++)
		scanf("%d", &A[i]);
	
		
	for (j = 0; j < num_numeros_a_buscar ;j++) {

			num= numeros_a_buscar[j];

			printf("\n\n------> Buscando %d\n", num);

			uswtime(&utime0, &stime0, &wtime0);

			for (int k = 1; k < NumThreads; k++) {
				if (pthread_create(&thread[k], NULL, procesar, (void*)k) != 0 ) 
				{
					perror("El thread no pudo crearse");
					exit(-1);
				}
			}

			procesar(0);

				
			//Esperar a que terminen los threads (Saludar)
			for (int k = 1; k < NumThreads; k++) pthread_join(thread[k], NULL);

			//Imprimir el numero si se encontro o no

			/*
			if(ind >= 0)
				printf("\n\nnumero encontrado en el lugar: %d\n\n",ind);
			else
				printf("\n\nel numero %d no se encuentra en el arreglo\n\n ",num);
			*/

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
	
	}
	


	//***************************************************************************************************************************
	// Calcular los tiempos de ejecuci�n
	//***************************************************************************************************************************
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

	
	free(A);
	return 0;

}

int lineal(int *a, int x, int inicio, int fin)
{
	int i;

	for (i = inicio; i < fin; i++)
		if ( x == a[i]) return i;
	return -1;
}

void *procesar(void *id)
{
	int n_thread = (int)id;
	int inicio, fin, i, cont = 0;
	inicio = (n_thread * n) / NumThreads;
	if (n_thread == NumThreads - 1)
		fin = n;
	else
		fin = ((n_thread + 1) * n) / NumThreads - 1;
	printf("EL thread %d inicia en %d y termina en %d\n", n_thread, inicio, fin);
	ind = lineal(A, num, inicio, fin);

	if(ind != -1)
	{
		printf("\nPosicion: %d\n", ind);
	}
	else if (cont != NumThreads)
	{
		cont++;
	}
	else
	{
		printf("El num: %d no se encontro", num);
	}
	

}
