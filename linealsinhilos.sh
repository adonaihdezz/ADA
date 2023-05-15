#!/bin/bash


gcc linealsinhilos.c tiempo.c -o linealsinhilos -w

./linealsinhilos < 10millones.txt > prueba.txt


#ejecutar en terminal: ./scriptFibonacci1.sh n n1 n2 n3
#ejemplo: ./scriptFibonacci1.sh 4 10000000 6 20

