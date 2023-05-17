#!/bin/bash


#COMPILAR EL DE HILOS
gcc linealconhilos.c tiempo.c -lpthread -o linealconhilos -w

n="$1"
output_file="Salidalinealconhilos.txt"

./linealconhilos "$n" 10000000 < 10millones.txt > "$output_file"
./linealconhilos "$n" 20000000 <numeros.txt >> "$output_file"
#./linealconhilos "$n" 30000000 <numeros.txt >> "$output_file"
#./linealconhilos "$n" 40000000 <numeros.txt >> "$output_file"
#./linealconhilos "$n" 50000000 <numeros.txt >> "$output_file"
#./linealconhilos "$n" 100000000 <numeros.txt >> "$output_file"

