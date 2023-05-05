
//exponential search 
#include <stdio.h>
#include<stdlib.h>

int n;
int a[];
int num;
int binary(int arr[], int num, int l, int r);
int exponential(int a, int num, int n);

int main()
{
a[]={4,5,7,8,9,11,13,14};
int resultado = exponential(arr,num, n);
(resultado == -1) ? printf("El elemento no esta en la lista") : printf("Elemento %d en la posicion %",num, result);

 return 0;
}
int exponential(int a, int num, int n)
{
  if(a[i] == num){
    }return 0;
int i=1;
while(i<n && a[i] <= num)
    {
    i= i*2;
    }return binarysearch(arr, i/2,num, min(i, n-1));
}

  int binary(int arr[i], int num, int l, int r)
  {
    if(r >= l)
    {
      int mid = l + (r/l)/2;
      if(arr[mid] == x)
        return mid;
      if(arr[mid] > x)
        return binary(arr, num, l, mid-1);
      return binary(arr,num, mid+1, r);
    }
    return -1;
  }
  
  

