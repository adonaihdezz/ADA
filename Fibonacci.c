/*
 * ANALISIS Y DISENO DE ALGORITMOS
 *
 *ALGORITMO HEAPSORT DE LA PRACTICA 1: IMPLEMENTACION Y ANALISIS DE EJECUCION DEL ALGORITMO FUBONACCI.
 * -------------------
 * EQUIPO: LOS BELICOS
 * 
 * VERSION DE CODIGO: 2
 * 
 *FECHA: 15/04/2023
 *
 *REALIZO: TORRES GUZMAN CESAR HAVIT
 *
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include "recursos/tiempo.h"
#include <pthread.h>

int NumThreads;			//N�mero de threads
int N,*A,num,n,ind=0;


void* saludar(void* id);
int min(int x, int y);
int fibMonaccianSearch(int *a, int x, int n);
void* procesar(void* id);


int main(int arg, char* argv[])
{
	int numeros_a_buscar[] = {322486, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644, 1295390003, 450057883, 187645041, 1980098116, 152503, 5000, 1493283650, 214826, 18433949527, 1360839354, 2109248666, 2147470852, 0};
    int tamanos_problema[] = {1000000, 2000000, 3000000, 4000000, 5000000, 10000000};

    int num_numeros_a_buscar = sizeof(numeros_a_buscar) / sizeof(numeros_a_buscar[0]);
    int num_tamanos_problema = sizeof(tamanos_problema) / sizeof(tamanos_problema[0]);
	int i,j,k,n2;
	double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medici�n de tiempos
	double utime02, stime02, wtime02,utime12, stime12, wtime12;
	

	pthread_t *thread;
	
	if (arg<2) 
	{
		printf("Indique el n�mero de threads - \tEjemplo: [user@equipo]$ %s 4\n\n",argv[0]);
		exit(-1);
	}
	
	NumThreads=atoi(argv[1]);
	thread = malloc(NumThreads*sizeof(pthread_t));
    
	if(arg != 3)
	{
		printf("\n\n Para compilar se necesita tamanio de arreglo");
		exit(1);
	}
	
    n= atoi(argv[2]);

    A = (int*) malloc(n * sizeof(int));
    
    //printf("para n: %d\n\n", n);
    
    for (i = 0; i < n; i++) 
    scanf("%d", &A[i]);

    
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
				
	
	printf("\n");
				
	//***************************************************************************************************************************
	//2 Procesar desde cada hilo "procesar"
	//*********************************************************************************************
	
	for (int k = 1; k < NumThreads; k++) 
	{
		if (pthread_create(&thread[k], NULL, procesar, (void*)k) != 0 ) 
		{
			perror("El thread no pudo crearse");
			exit(-1);
		}
	}

	for (i = 0; i < num_tamanos_problema ;i++) {
		printf("\n\npara n: %d\n\n", tamanos_problema[i]);
		for (j = 0; j < num_numeros_a_buscar ;j++) {
			num= numeros_a_buscar[j];
			n = tamanos_problema[i];
			
			//printf("Buscando %d en un arreglo de tamaño %d con %d hilos:\n", num, n, NumThreads);



			uswtime(&utime0, &stime0, &wtime0);
			procesar(0);
			uswtime(&utime1, &stime1, &wtime1);

			utime02+=utime0;
			stime02+=stime0;
			wtime02+=wtime0;
			utime12+=utime1;
			stime12+=stime1;
			wtime12+=wtime1;
	

			
			//Esperar a que terminen los threads (Saludar)
			for (int k = 1; k < NumThreads; k++) pthread_join(thread[k], NULL);
			/*
			if(ind >= 0)
				printf("\n\nnumero encontrado en el lugar: %d\n\n",ind);
			else
				printf("\n\nel numero %d no se encuentra en el arreglo\n\n ",num);
			*/
	
		}
			printf("\nTiempo de ejecucion del programa\n");
			printf("real (Tiempo total):  %.10f s\n",  wtime12 - wtime02);
			printf("user (Tiempo de procesamiento en CPU): %.10f s\n",  utime12 - utime02);
			printf("sys (Tiempo en acciónes de E/S):  %.10f s\n",  stime12 - stime02);
			printf("CPU/Wall:   %.10f %% \n",100.0 * (utime12 - utime02 + stime12 - stime02) / (wtime12 -wtime02));
			printf("\n");
			
			//Mostrar los tiempos en formato exponecial
			printf("\nFormato exponencial\n");
			printf("real (Tiempo total):  %.10e s\n",  wtime12 - wtime02);
			printf("user (Tiempo de procesamiento en CPU): %.10e s\n",  utime12 - utime02);
			printf("sys (Tiempo en acciónes de E/S):  %.10e s\n",  stime12 - stime02);
			printf("CPU/Wall:   %.10f %% \n",100.0 * (utime12 - utime02 + stime12 - stime02) / (wtime12 - wtime02));
			printf("\n");
		printf("\n\n**************************************\n\n");
		utime02=0;
		stime02=0;
		wtime02=0;
		utime12=0;
		stime12=0;
		wtime12=0;
	
	}	
	
	

	
 
	/*
	printf("\nTiempo de ejecucion del programa\n");
	printf("real (Tiempo total):  %.10f s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU): %.10f s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S):  %.10f s\n",  stime1 - stime0);
	printf("CPU/Wall:   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 -wtime0));
	printf("\n");
	
	//Mostrar los tiempos en formato exponecial
	printf("\nFormato exponencial\n");
	printf("real (Tiempo total):  %.10e s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU): %.10e s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S):  %.10e s\n",  stime1 - stime0);
	printf("CPU/Wall:   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	
	printf("******************************************************************");
   	printf("\n");	

	*/

	
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



void* procesar(void* id)
{	
	int n_thread=(int)id;
	int inicio,fin,i;

	//Revisar la parte de los datos a procesar	
	inicio=(n_thread*n)/NumThreads;
	if(n_thread==NumThreads-1)	
		fin=n;
	else
		fin=((n_thread+1)*n)/NumThreads-1;
	

	//printf("\nHola desde procesar\tSoy el thread %d\tInicio %d\tTermino %d",n_thread,inicio,fin);
	
	ind = fibMonaccianSearch(A, num, n);

	//printf("\nBye desde procesar\tSoy el thread %d\tHe terminado",n_thread);

}

void* saludar(void* id)
{
	printf("\nHola desde Saludar\tSoy el thread %d", (int)id);
}
