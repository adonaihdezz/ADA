#!/bin/bash

gcc Exponencialsinhilos.c tiempo.c -o Exponentialsinhilos -w 
./Exponentialsinhilos 10000000 < 10millones.txt > SalidaExponencialsinhilos.txt 
# Cambia el tamano del arreglo (n)
# ./Exponencialsinhilos.sh 
