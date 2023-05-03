#!/bin/bash
gcc martes2.c tiempo.c -lpthread -o martes2 -w

./martes2 4 100000 207442309 < numeros.txt # > sallunes.txt 
