//exponential search 
#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#include<pthread.h>
#include "tiempo.h"

int NumThreads;
int n;
//int a;
int num;
int *A;
int ind = -1;


int binary(int *a, int num, int l, int r);

int exponential(int *a, int num, int n);

 int min(int a, int b);
 
 void* procesar(void* id);
 
 

int main(int arg, char *argv[])
{
	int i, tmp;
	//printf("tamano del problema y num a buscar");
	double utime0, stime0, wtime0,utime1, stime1, wtime1;
		pthread_t *thread;
			
	if(arg <2)
	{
	printf("Indique el numero de threads %s\n", argv[0]);
	exit(-1);
	}
	NumThreads = atoi(argv[1]);
	thread = malloc(NumThreads*sizeof(pthread_t));
	if(argv != 4)
	{
	printf("Ingrese el tamano del arreglo y el numero a buscar");
	exit(1);
	}
		n = atoi(argv[2]);
		num = atoi(argv[3]);
		
	A=(int*)malloc(n*sizeof(int));
	
	for(i = 0; i < n; i++)
	{
	scanf("%d",&A[i]);
	}
	
	for(i = 1; i < NumThreads; i++)
	{
		if(pthread_create(&thread[i],NULL,(void*)i)!= 0){
		perror("El thread no pudo crearse");
		exit(-1);
		}
	}
	for(i = 1; i<NumThreads; i++)
	pthread_join(thread[i],NULL);
	
	for(i = 1; i< NumThreads;i++)
	{
	if(pthread_create(&pthread[i],NULL,procesar,(void*)i)!= 0){
		perror("El thread no pudo crearse");
		exit(-1)
		}
	}
	uswtime(&utime0, &stime0, &wtime0);
	procesar(0);
	uswtime(&utime1, &stime1, &wtime1);
	
	for(i = 1; i<NumThreads; i++)
	{
		tmp = pthread_join (thread[i],NULL);
		if(tmp != -1)
		{
		ind = temp;
		}
	}
	if(ind!=-1){
		printf("\n\nnumero encontrado en el lugar: %d\n\n",ind);
	}else
		printf("\n\nel numero %d no se encuentra en el arreglo\n\n ",num);
	
	printf("\nTiempo de ejecucion del programa\n");
	printf("real (Tiempo total):  %.10f s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU): %.10f s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciÃ³nes de E/S):  %.10f s\n",  stime1 - stime0);
	printf("CPU/Wall:   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 -wtime0));
	printf("\n");
	
	//Mostrar los tiempos en formato exponecial
	printf("\nFormato exponencial\n");
	printf("real (Tiempo total):  %.10e s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU): %.10e s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciÃ³nes de E/S):  %.10e s\n",  stime1 - stime0);
	printf("CPU/Wall:   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	
	printf("******************************************************************");
   	printf("\n");	

	
	free(A);
	return 0;
	
	// codigo sin threads 
	
//	int resultado = exponential(A,num, n);
//	(resultado == -1) ? printf("El elemento no esta en la lista") : printf("Elemento %d en la posicion %d",num, resultado+1);

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

 void* procesar(void* id)
 {
 int n_thread = (int)id;
 int inicio, fin, i;
 inicio = (n_thread*n)/NumThreads;
 if(n_thread == NuThreads-1)
 	fin = n;
 else
 	fin= ((n_thread+1)*n)/NumThreads-1;
 printf("El thread %d inicia en %d y termina en %d", n_thread, inicio, fin);
 
 	ind = exponential(A,num, n);
 }
