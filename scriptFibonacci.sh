#!/bin/bash
gcc fibonacci.c recursos/tiempo.c -lpthread -o fibonacci

./fibonacci 4 10000000 < numeros.txt > salFibonacci.txt
./fibonacci 4 20000000 < numeros.txt >> salFibonacci.txt
./fibonacci 4 30000000 < numeros.txt >> salFibonacci.txt
./fibonacci 4 40000000 < numeros.txt >> salFibonacci.txt
./fibonacci 4 50000000 < numeros.txt >> salFibonacci.txt
./fibonacci 4 100000000 < numeros.txt >> salFibonacci.txt
