#!/bin/bash


#COMPILAR EL DE HILOS
gcc Exponencialconhilos.c tiempo.c -lpthread -o Exponencialconhilos -w

n="$1"
output_file="SalidaExponencialconhilos.txt"

./Exponencialconhilos "$n" 10000000 < 10millones.txt > "$output_file"
#./Exponencialconhilos "$n" 20000000 <numeros.txt >> "$output_file"
#./Exponencialconhilos "$n" 30000000 <numeros.txt >> "$output_file"
#./Exponencialconhilos "$n" 40000000 <numeros.txt >> "$output_file"
#./Exponencialconhilos "$n" 50000000 <numeros.txt >> "$output_file"
#./Exponencialconhilos "$n" 100000000 <numeros.txt >> "$output_file"

