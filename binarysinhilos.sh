#!/bin/bash

gcc binarysinhilos.c tiempo.c -o binarysinhilos 

./binarysinhilos 10000000 < 10millones.txt > SalidaBinarySinHilos.txt
#cambian tamano del arreglo
# ./binarysinhilos.sh
