#!/bin/bash

#COMPILAR BINARY

gcc BinarySearch25.c tiempo.c -lpthread -o BinarySearch25

n="$1"
output_file="SalidaBinary.txt"

./BinarySearch25 "$n" 10000000 < 10millones.txt > "$output_file"
#./BinarySearch25 "$n" 20000000 <numeros.txt >> "$output_file"
#./BinarySearch25 "$n" 30000000 <numeros.txt >> "$output_file"
#./BinarySearch25 "$n" 40000000 <numeros.txt >> "$output_file"
#/BinarySearch25 "$n" 50000000 <numeros.txt >> "$output_file"
#./BinarySearch25 "$n" 100000000 <numeros.txt >> "$output_file"
