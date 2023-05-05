#!/bin/bash

gcc exponential.c tiempo.c -lpthread -o exponential -w 
./ exponential 1000 207442309 < numeros.txt > expo_salida.txt
