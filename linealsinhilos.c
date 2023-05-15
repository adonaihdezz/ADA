#include <stdio.h>
#include <stdlib.h>
#include "tiempo.h"


int n, num, *A;

int lineal(int *a, int num, int n);

int main(int arg, char *argv[])
{
	int i;
	int numeros_a_buscar[] = {162312,0,197,2096,2293};
	int num_numeros_a_buscar = sizeof(numeros_a_buscar) / sizeof(numeros_a_buscar[0]);
	
	double utime0, stime0, wtime0, utime1, stime1, wtime1;
	double utime02, stime02, wtime02,utime12, stime12, wtime12;
	
	
	n = atoi(argv[1]);
	
	A = (int *)malloc(n * sizeof(int));
	
	for(i = 0; i < n; i++)
	{
		scanf("%d",&A[i]);
	}
	for(i = 0; i < num_numeros_a_buscar; i++)
	{
	int posicion = lineal(A,numeros_a_buscar[i], n);
	if(posicion != -1)
	{
		printf("%d en la posicion %d\n", numeros_a_buscar[i], posicion);
	}else	{
	printf("%ld no encontrado\n",numeros_a_buscar[i]);
		}
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
