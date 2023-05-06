#!/bin/bash


#COMPILAR EL DE HILOS
gcc fibonacci_conHilos.c recursos/tiempo.c -lpthread -o fibonacci_conHilos
#COMPILAR EL DE SIN HILOS
gcc fibonacci_sinHilos.c recursos/tiempo.c -o fibonacci_sinHilos

# Parámetros a pasar al programa DE HILOS
n="$1"
output_file="salFibonacci_conHilos.txt"

./fibonacci_conHilos "$n" 10000000 <numeros.txt > "$output_file"
./fibonacci_conHilos "$n" 20000000 <numeros.txt >> "$output_file"
./fibonacci_conHilos "$n" 30000000 <numeros.txt >> "$output_file"
./fibonacci_conHilos "$n" 40000000 <numeros.txt >> "$output_file"
./fibonacci_conHilos "$n" 50000000 <numeros.txt >> "$output_file"
./fibonacci_conHilos "$n" 100000000 <numeros.txt >> "$output_file"



# Parámetros a pasar al programa SIN HILOS
n2="$2"
n3="$3"
n4="$4"
output_file="salFibonacci_sinHilos.txt"

# Ejecuta el programa con los parámetros y los archivos de texto
./fibonacci_sinHilos "$n2" "$n3" "$n4" numeros.txt tamano.txt numero.txt > "$output_file"
