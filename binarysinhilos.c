/*
 * ANALISIS Y DISENO DE ALGORITMOS
 *
 *ALGORITMO BINARY SEARCH DE LA PRACTICA 1: IMPLEMENTACION Y ANALISIS DE EJECUCION DEL ALGORITMO.
 * -------------------
 * EQUIPO: LOS BELICOS
 * 
 * VERSION DE CODIGO: 2.4 Binaria sin hilos
 * 
 *FECHA:15/O5/2023
 *
 *REALIZO: PRIEGO SUAREZ DAVID SALVADOR
 *
 *
 */   

#include <stdio.h>
#include <stdlib.h>
#include "tiempo.h"



int *arr=NULL,n,num, posicion;
int binarySearch(int arr[], int l, int r, int x);

int main(int arg,char * argv[]){
	int i,j;
	
    long long int numeros_a_buscar[] = {322486, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644, 1295390003, 450057883, 187645041, 1980098116, 152503, 5000, 1493283650, 214826, 18433949527, 1360839354, 2109248666, 2147470852, 0};
	int num_numeros_a_buscar = sizeof(numeros_a_buscar) / sizeof(numeros_a_buscar[0]);
	
    double utime0, stime0, wtime0, utime1, stime1, wtime1;
	double utime02, stime02, wtime02,utime12, stime12, wtime12;
    
	
    n= atoi(argv[1]);
    num = atoi(argv[3]);

    arr = (int*) malloc(n * sizeof(int));
    
        for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    uswtime(&utime0, &stime0, &wtime0);
    
	//f tendra en fin del arreglo
    int f = n;
	//Llama a la funci�n de busquda y envia un resultado a posicion
	//dependiendo del valor en result sabremos si se encuentro el valor.

    for(i = 0; i < num_numeros_a_buscar; i++)
	{
	uswtime(&utime0, &stime0, &wtime0);
	posicion = binarySearch(arr, 0, f - 1, numeros_a_buscar[i]);
	uswtime(&utime1, &stime1, &wtime1);
	if(posicion != -1)
	{
		printf("%lld en la posicion %d\n", numeros_a_buscar[i], posicion);
	}else	{
	printf("%lld no encontrado\n",numeros_a_buscar[i]);
		}
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
	free(arr);
	
	return 0;

}

int binarySearch(int arr[], int l, int r, int x) //Llamada a la funci�n con el valor a buscar, inicio y fin,
{
    if (r >= l) { //El ciclo se realiza mientras el fin sea mayor o igual al inicio
        int mid = l + (r - l) / 2; 
 
        // Si el elemento presente esta en el medio
        // retorna el valor
        if (arr[mid] == x)
            return mid;
 
        //  Si el elemento a buscar es menor que el valor medio
        // Se vuelve a llamar a la funci�n binarySearch pero solo se envia el lado izquierdo del arreglo
        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);
 
        // Si el elemento a buscar es mayor que el valor medio
        //Se vuelve a llamar a la funci�n binarySearch pero solo se envia el lado derecho del arreglo
        return binarySearch(arr, mid + 1, r, x);
    }
 
    // Si el elemento a buscar no esta presente 
    // se retorna el valor de -1
    return -1;
}

