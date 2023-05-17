/*
Analisis y diseno de algoritmos 

Equipo: Los belicos 

Version del codigo: 8 Exponencial sin hilos 

Fecha: 05/05/2023

Realizo: Jesus Adonai Perez Hernandez

*/
#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#include "tiempo.h"

int *A, resultado, n, num;

int binary(int *a, int num, int l, int r);

int exponential(int *a, int num, int n);

int min(int a, int b);

void *procesar(void *id);

int main(int arg, char *argv[])
{
	int i;
	int numeros_a_buscar[] = {322486, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644, 1295390003, 450057883, 187645041, 1980098116, 152503, 5000, 1493283650, 214826, 18433949527, 1360839354, 2109248666, 2147470852, 0};
	int num_numeros_a_buscar = sizeof(numeros_a_buscar) / sizeof(numeros_a_buscar[0]);
	
	double utime0, stime0, wtime0, utime1, stime1, wtime1;
	double utime02, stime02, wtime02,utime12, stime12, wtime12;

	n = atoi(argv[1]);
		
	A=(int*)malloc(n*sizeof(int));


	for(i = 0; i < n; i++)
	{
	scanf("%d",&A[i]);
	}

	uswtime(&utime0, &stime0, &wtime0);

	for(i = 0; i < num_numeros_a_buscar; i++)
	{

	int posicion = exponential(A,numeros_a_buscar[i], n);


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
	}

	free(A);
 	return 0;
 
}


int exponential(int *a, int num, int n)
{
 if(a[0] == num)
return 0;
   
 int i=1;
while(i<n && a[i] <= num)
    {
    i= i*2;
    }
    return binary(a, num, i/2, min(i, n-1));
}


  int binary(int *a, int num, int l, int r)
  {
    if(r >= l)
    {
      int mid = l + (r-l)/2;
      if(a[mid] == num){
      return mid;
      }  
      if(a[mid] > num){
        return binary(a, num, l, mid-1);
        }
      return binary(a,num, mid+1, r);
    }
    return -1;
  }
  
 int min(int a, int b)
{
    return (a < b) ? a : b;
}

	