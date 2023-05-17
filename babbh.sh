#!/bin/bash
gcc babbh.c -o babbh tiempos/tiempo.c

./babbh 1000000 > babbh_salida.txt < numeros.txt 
