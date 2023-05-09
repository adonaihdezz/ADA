#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "tiempo.h"


int NumThreads;
int N, *A, num, n, ind = -1;

int busquedalineal(int *a, int x, int inicio, int fin);
void *procesar(void *id);

int main(int arg, char *argv[])
{
	int i, j, k, tmp;
	double utime0, stime0, wtime0, utime1, stime1, wtime1;
	pthread_t *thread;

    if (arg < 2)
	{
		printf("Indique el numero de threads %s\n", argv[0]);
		exit(-1);
	}
	NumThreads = atoi(argv[1]);
	thread = malloc(NumThreads * sizeof(pthread_t));
	if (arg != 4)
	{
		printf("Ingrese tamano del arreglo y numero a buscar");
		exit(1);
	}
	n = atoi(argv[2]);
	num = atoi(argv[3]);

	A = (int *)malloc(n * sizeof(int));
    printf("para n: %d\n", n);

    for (i = 0; i < n; i++)
	{
		scanf("%d", &A[i]);
	}

	uswtime(&utime0, &stime0, &wtime0);

    for (i = 1; i < NumThreads; i++)
	{
		if (pthread_create(&thread[i], NULL, procesar, (void *)i) != 0)
		{
			perror("El thread no pudo crearse");
			exit(-1);
		}
	}
	procesar(0);
	
    for (i = 1; i < NumThreads; i++)
		pthread_join(thread[i], NULL);

	uswtime(&utime1, &stime1, &wtime1);

    	printf("\nTiempo de ejecucion del programa\n");
	printf("real (Tiempo total):  %.10f s\n", wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU): %.10f s\n", utime1 - utime0);
	printf("sys (Tiempo en acciÃ³nes de E/S):  %.10f s\n", stime1 - stime0);
	printf("CPU/Wall:   %.10f %% \n", 100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");

	// Mostrar los tiempos en formato exponecial
	printf("\nFormato exponencial\n");
	printf("real (Tiempo total):  %.10e s\n", wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU): %.10e s\n", utime1 - utime0);
	printf("sys (Tiempo en acciÃ³nes de E/S):  %.10e s\n", stime1 - stime0);
	printf("CPU/Wall:   %.10f %% \n", 100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");

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