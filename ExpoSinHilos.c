//exponential search 
#include <stdio.h>
#include<stdlib.h>
#include <math.h>
int n;
//int a;
int num;
int *A;


int binary(int *a, int num, int l, int r);

int exponential(int *a, int num, int n);

 int min(int a, int b);

int main(int arg, char *argv[])
{
	int i;
	//printf("tamano del problema y num a buscar");
	
		n = atoi(argv[1]);
		num = atoi(argv[2]);
		
	A=(int*)malloc(n*sizeof(int));
	
	for(i = 0; i < n; i++)
	{
	scanf("%d",&A[i]);
	}
	
	int resultado = exponential(A,num, n);
	(resultado == -1) ? printf("El elemento no esta en la lista") : printf("Elemento %d en la posicion %d",num, resultado+1);

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
