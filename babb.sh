#!/bin/bash
gcc babb.c -o babb tiempos/tiempo.c

./babb 1000000 > babb_salida.txt < numeros.txt 
