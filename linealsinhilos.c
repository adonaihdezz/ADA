/*
Analisis y diseno de algoritmos 

Equipo: Los belicos 

Version del codigo: 7 Lineal sin hilos 

Fecha: 05/05/2023

Realizo: Jesus Adonai Perez Hernandez

*/
#include <stdio.h>
#include <stdlib.h>
#include "tiempo.h"


int n, num, *A;

int lineal(int *a, int num, int n);

int main(int arg, char *argv[])
{
	int i;
	int numeros_a_buscar[] = {322486, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644, 1295390003, 450057883, 187645041, 1980098116, 152503, 5000, 1493283650, 214826, 18433949527, 1360839354, 2109248666, 2147470852, 0};
	int num_numeros_a_buscar = sizeof(numeros_a_buscar) / sizeof(numeros_a_buscar[0]);
	
	double utime0, stime0, wtime0, utime1, stime1, wtime1;
	double utime02, stime02, wtime02,utime12, stime12, wtime12;
	
	
	n = atoi(argv[1]);
	
	A = (int *)malloc(n * sizeof(int));
	
	for(i = 0; i < n; i++)
	{
		scanf("%d",&A[i]);
	}
	
	uswtime(&utime0, &stime0, &wtime0);
	
	for(i = 0; i < num_numeros_a_buscar; i++)
	{
	int posicion = lineal(A,numeros_a_buscar[i], n);
	if(posicion != -1)
	{
		printf("%d en la posicion %d\n", numeros_a_buscar[i], posicion);
	}else	{
	printf("%ld no encontrado\n",numeros_a_buscar[i]);
		}
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
		
	
	uswtime(&utime1, &stime1, &wtime1);
	
				

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

int lineal(int *a, int num, int n)
{
	int i;
	
	for(i = 0; i< n; i++)
	{
		if(num == a[i])
		{
			return i;
		}
		
	}
	return -1;
}
