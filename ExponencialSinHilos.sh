#!/bin/bash

gcc exponential.c tiempo.c -o exponential -w 
./exponential 1000000 197 < 10millones.txt #>> expo_salida.txt

