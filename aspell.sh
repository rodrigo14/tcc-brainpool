#!/bin/bash

for file in $@ #contém argumentos passados por linha de comando
do
	aspell -d pt_BR -c $file
done
