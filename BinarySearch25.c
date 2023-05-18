/*
 * ANALISIS Y DISENO DE ALGORITMOS
 *
 *ALGORITMO BINARY SEARCH DE LA PRACTICA 1: IMPLEMENTACION Y ANALISIS DE EJECUCION DEL ALGORITMO FUBONACCI.
 * -------------------
 * EQUIPO: LOS BELICOS
 * 
 * VERSION DE CODIGO: 2.2
 * 
 *FECHA:08/O5/2023
 *
 *REALIZO: PRIEGO SUAREZ DAVID SALVADOR
 *
 *
 */   


#include <stdio.h>
#include <stdlib.h>
#include "tiempo.h"
#include <pthread.h>

int NumThreads;			//N�mero de threads
int N,*A=NULL,num,n,ind=0,f;

void* saludar(void* id);
int binarySearch(int A[], int x, int r, int l);
void* procesar(void* id);


int main(int arg,char * argv[]){
	
	long int numeros_a_buscar[] = {322486, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644, 1295390003, 450057883, 187645041, 1980098116, 152503, 5000, 1493283650, 214826, 18433949527, 1360839354, 2109248666, 2147470852, 0};	
	int num_numeros_a_buscar = sizeof(numeros_a_buscar) / sizeof(numeros_a_buscar[0]);

	int i,j,k;
	double utime0, stime0, wtime0, utime1, stime1, wtime1;
	double utime02, stime02, wtime02,utime12, stime12, wtime12;
	
	pthread_t *thread;

	if (arg<2) 
	{
		printf("Indique el numero de threads %s\n", argv[0]);
		exit(-1);
	}
	
	NumThreads=atoi(argv[1]);
	//un puntero asignado al inicio del espacio de memoria del tamano de un thread
	thread = malloc(NumThreads*sizeof(pthread_t));
	
	if(arg != 3) exit(1);

	n= atoi(argv[2]);
    A = (int*) malloc(n * sizeof(int));
    
    
   //******************************************************************************  
    //1 Saludar desde cada hilo "saludar"
	//***************************************************************************************************************************
	//Crear los threads con el comportamiento "segmentar"
	for (i=1; i<NumThreads; i++) 
	{
		if (pthread_create (&thread[i], NULL, saludar,(void*)i) != 0 ) 
		{
			perror("El thread no  pudo crearse");
			exit(-1);
		}
	}
	
	//El main ejecuta el thread 0
	saludar(0);
	
	
	//Esperar a que terminen los threads (Saludar)
	for (i=1; i<NumThreads; i++) pthread_join (thread[i], NULL);
				
	
	printf("para n: %d\n", n);
    
	//***************************************************************************************************************************
	//2 Procesar desde cada hilo "procesar"
	//*********************************************************************************************
	    
	//f tendra en fin del arreglo
    f = n;
    
	for(i=0; i < n; i++ )
	scanf("%d",&A[i]);
	for(j=0; j<num_numeros_a_buscar; j++){
		num= numeros_a_buscar[j];

		printf("\n\n------> Buscando %d\n", num);
			uswtime(&utime0, &stime0, &wtime0);

	for (k=1; i<NumThreads; k++) 
	{
		if (pthread_create (&thread[k], NULL, procesar,(void*)k) != 0 ) 
		{
			perror("El thread no  pudo crearse");
			exit(-1);
		}
	}

			procesar(0);

			uswtime(&utime1, &stime1, &wtime1);
	
			for (int k = 1; k < NumThreads; k++) pthread_join(thread[k], NULL);

			//Imprimir el numero si se encontro o no

			
			/*if(ind >= 0)
				printf("\n\nnumero encontrado en el lugar: %d\n\n",ind);
			else
				printf("\n\nel numero %d no se encuentra en el arreglo\n\n ",num);
			//*/


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
	printf("\n\n**************\n\n");
	}
	free(A);
	return 0;
}

int binarySearch(int *a, int x, int r, int l) //Llamada a la funci�n con el valor a buscar, inicio y fin,
{
    if (r >= l) { //El ciclo se realiza mientras el fin sea mayor o igual al inicio
        int mid = l + (r - l) / 2; 
 
        // Si el elemento presente esta en el medio
        // retorna el valor
        if (a[mid] == x)
            return mid;
 
        //  Si el elemento a buscar es menor que el valor medio
        // Se vuelve a llamar a la funci�n binarySearch pero solo se envia el lado izquierdo del arreglo
        if (a[mid] > x)
            return binarySearch(a, x, mid - 1, l);
 
        // Si el elemento a buscar es mayor que el valor medio
        //Se vuelve a llamar a la funci�n binarySearch pero solo se envia el lado derecho del arreglo
        return binarySearch(a, x, r, mid + 1);
    }
 
    // Si el elemento a buscar no esta presente 
    // se retorna el valor de -1
    return -1;
}



void *procesar(void* id)
{	
	int n_thread=(int)id;
	int inicio,fin,i;

	//Revisar la parte de los datos a procesar	
	inicio=(n_thread*n)/NumThreads;
	if(n_thread==NumThreads-1)	
		fin=n;
	else
		fin=((n_thread+1)*n)/NumThreads-1;

	printf("\nHola desde procesar\tSoy el thread %d\tInicio %d\tTermino %d",n_thread,inicio,fin);
	
	ind = binarySearch(A, num, f - 1, 0);

	printf("\nBye desde procesar\tSoy el thread %d\tHe terminado",n_thread);

}

void* saludar(void* id)
{
	printf("\nHola desde Saludar\tSoy el thread %d", (int)id);
}
