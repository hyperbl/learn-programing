#! /bin/bash
gcc -o3 bfc.c -o bfc.o
./bfc.o $1
str=$1
gcc -o3 a.c -o  ${str%.*}.o
rm -rf a.c bfc.o