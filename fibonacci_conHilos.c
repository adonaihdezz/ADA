/*
 * ANALISIS Y DISENO DE ALGORITMOS
 *
 *ALGORITMO HEAPSORT DE LA PRACTICA 1: IMPLEMENTACION Y ANALISIS DE EJECUCION DEL ALGORITMO FUBONACCI.
 * -------------------
 * EQUIPO: LOS BELICOS
 * 
 * VERSION DE CODIGO: 14.0
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
#include <pthread.h>

int NumThreads;			//N�mero de threads
int *A,n,ind;
long int num;

void* procesar(void* id);
void fibMonaccianSearch(int *a, int inicio, int fin,long int num);
void* saludar(void* id);
int min(int x, int y);


int main(int arg, char* argv[])
{
	//aqui si dejo este arreglo
	long int numeros_a_buscar[] = {322486, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644, 1295390003, 450057883, 187645041, 1980098116, 152503, 5000, 1493283650, 214826, 18433949527, 1360839354, 2109248666, 2147470852, 0};
    int num_numeros_a_buscar = sizeof(numeros_a_buscar) / sizeof(numeros_a_buscar[0]);

	int i,j,k;
	double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medici�n de tiempos
	double utime02, stime02, wtime02,utime12, stime12, wtime12;
	

	pthread_t *thread;
//***************************************************************************************************************************
// Verificar par�metros y llenar el arreglo
//***************************************************************************************************************************	
	if (arg<2) 
	{
		printf("Indique el n�mero de threads - \tEjemplo: [user@equipo]$ %s 4\n\n",argv[0]);
		exit(-1);
	}
	
	NumThreads=atoi(argv[1]);
	thread = malloc(NumThreads*sizeof(pthread_t));

	ind=-1;
    
	if(arg != 3)
	{
		printf("\n\n Para compilar se necesita tamanio de arreglo");
		exit(1);
	}
	
	//aqui lo deje igual como lo haciamos antes
    n= atoi(argv[2]);
    A = (int*) malloc(n * sizeof(int));
    
    
    for (i = 0; i < n; i++) 
    scanf("%d", &A[i]);

	printf("\n--------------------------Implementacion con hilos----------------------------- \n\n");
//***************************************************************************************************************************

//***************************************************************************************************************************
// Buscar cada n�mero en el arreglo
//***************************************************************************************************************************
	printf("\n\npara n: %d con %d hilos\n\n",n, NumThreads);


	//esto ya lo explicamos en clase
	for (j = 0; j < num_numeros_a_buscar ;j++) {

			num= numeros_a_buscar[j];
			ind=-1;
			printf("\n\n------> Buscando %ld\n", num);

			uswtime(&utime0, &stime0, &wtime0);

			for (k = 1; k < NumThreads; k++) {
				if (pthread_create(&thread[k], NULL, procesar, (void*)k) != 0 ) 
				{
					perror("El thread no pudo crearse");
					exit(-1);
				}
			}

			procesar(0);

				
			//Esperar a que terminen los threads (Saludar)
			for (k = 1; k < NumThreads; k++) 
				pthread_join(thread[k], NULL);

			//Imprimir el numero si se encontro o no

			uswtime(&utime1, &stime1, &wtime1);

			if(ind != -1 )
				printf("\n\nnumero encontrado en el lugar: %d\n\n",ind);
			else
				printf("\n\nel numero %ld no se encuentra en el arreglo\n\n ",num);


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

/*
DESCRIPCION:La funcion min encuentra el minimo entre dos numeros. 
PARAMETRO x: Numero a comparar.
PARAMETRO y: numero a comparar.

RETORNO:Retorna el numero mas peque�o entre los 2.
*/

int min(int x, int y)
{ return (x <= y) ? x : y; }


/*
DESCRIPCION:
	La funcion fibMonaccianSearch es una busqueda aplicando la sucesion de fibonacci, donde se compara el numero a buscar 
	con el A[i] y se mueve el inicio y fin de la busqueda dependiendo del resultado de la comparacion.
	en esta version se utiliza hilos para realizar la busqueda, donde cada hilo se encarga de una parte del arreglo.
	de forma que para obtener el indice del numero buscado se compara el inicio y fin de cada hilo con el numero buscado.

ENTRADA:
	*a: Arreglo donde se va a buscar el numero.
	inicio: Posicion inicial del arreglo.
	fin: Posicion final del arreglo.
	n: Numero a buscar.

RETORNO: No retorna nada.
*/

void fibMonaccianSearch(int *a, int inicio,int fin, long int num)
{
	if (ind!=-1)
		return;

	
	// Inicializar los numeros de fibonacci
	int fibMMm2 = 0; // (m-2)'th Fibonacci No.
	int fibMMm1 = 1; // (m-1)'th Fibonacci No.
	int fibM = fibMMm2 + fibMMm1; // m'th Fibonacci

	//fibM es el numero de fibonacci mas peque�o mayor o igual a n
	while (ind == -1 && fibM < fin-inicio) {
		fibMMm2 = fibMMm1;
		fibMMm1 = fibM;
		fibM = fibMMm2 + fibMMm1;
	}

	// marcamos el rango eliminado desde el frente
	int offset = -1;

	//mientras que haya elementos para inspeccionar, fibMm2 se compara con x. Cuando fibM se vuelve 1, fibMm2 se vuelve 0 y se termina el ciclo. 
	while (ind ==-1 && fibM > 1) {

		//chequeamos si fibMm2 es una posicion valida
		int i = min(offset + fibMMm2, fin - inicio - 1);


		//si x es mayor que el valor en la posicion fibMm2, cortamos el subarreglo desde offset hasta i
		if (a[i+inicio] < num) {
			fibM = fibMMm1;
			fibMMm1 = fibMMm2;
			fibMMm2 = fibM - fibMMm1;
			offset = i;
		}

		//si x es mayor que el valor en la posicion fibMm2, cortamos el subarreglo despues de i+1
		else if (a[i+inicio] > num) {
			fibM = fibMMm2;
			fibMMm1 = fibMMm1 - fibMMm2;
			fibMMm2 = fibM - fibMMm1;
		}

		//elemento encontrado, y asignamos el indice
		else
			ind=i+inicio;

	}

	//comparamos el ultimo elemento con num

	if (ind==-1 && fibMMm1 && a[offset + inicio + 1] == num){

		ind = offset + inicio + 1;
		printf("\n\nel numero se encuentra en la posicion %d\n\n ",inicio);
	}

}


/*
DESCRIPCION:La funcion procesar es la funcion que ejecutan los threads.
			es la funcion que define el inicio y fin de la busqueda para cada thread.
			dependiendo del numero de threads que se definan, se divide el arreglo en partes iguales.
PARAMETRO id: Identificador del thread.
*/
void* procesar(void* id){	
	int n_thread=(int)id;
	int inicio,fin,i;

	//Revisar la parte de los datos a procesar	
	inicio=(n_thread*n)/NumThreads;
	if(n_thread==NumThreads-1)	
		fin=n;
	else
		fin=(((n_thread+1)*n)/NumThreads)-1;	
	

	//printf("\nHola desde procesar\tSoy el thread %d\tInicio %d\tTermino %d",n_thread,inicio,fin);
	
	fibMonaccianSearch(A, inicio,fin, num);

	//printf("\nBye desde procesar\tSoy el thread %d\tHe terminado",n_thread);

}

