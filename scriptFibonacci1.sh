#!/bin/bash

gcc fibonacci_conHilos.c recursos/tiempo.c -lpthread -o fibonacci_conHilos
gcc fibonacci_sinHilos.c recursos/tiempo.c -o fibonacci_sinHilos


./fibonacci_conHilos 4 1000000 < numeros.txt >> salFibonacci_conHilos.txt
./fibonacci_conHilos 4 2000000 < numeros.txt >> salFibonacci_conHilos.txt
./fibonacci_conHilos 4 3000000 < numeros.txt >> salFibonacci_conHilos.txt
./fibonacci_conHilos 4 4000000 < numeros.txt >> salFibonacci_conHilos.txt
./fibonacci_conHilos 4 5000000 < numeros.txt >> salFibonacci_conHilos.txt
./fibonacci_conHilos 4 10000000 < numeros.txt >> salFibonacci_conHilos.txt


./fibonacci_sinHilos 1000000 < numeros.txt > salFibonacci_sinHilos.txt
./fibonacci_sinHilos 2000000 < numeros.txt >> salFibonacci_sinHilos.txt
./fibonacci_sinHilos 3000000 < numeros.txt >> salFibonacci_sinHilos.txt
./fibonacci_sinHilos 4000000 < numeros.txt >> salFibonacci_sinHilos.txt
./fibonacci_sinHilos 5000000 < numeros.txt >> salFibonacci_sinHilos.txt
./fibonacci_sinHilos 10000000 < numeros.txt >> salFibonacci_sinHilos.txt

