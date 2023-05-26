#!/bin/bash

gcc Huffman.c -o Huffman recursos/tiempo.c

./Huffman pruebapdf.pdf > codigos.txt
