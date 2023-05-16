#!/bin/bash


gcc linealsinhilos.c tiempo.c -o linealsinhilos -w

./linealsinhilos 10000000 < 10millones.txt > SalidaLinealSinHilos.txt
#Cambian tamano del arreglo 
# ./linealsinhilos.sh  
