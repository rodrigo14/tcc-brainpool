#!/bin/bash

for file in editaveis/text_*.tex
do
	aspell -d pt_BR -c $file
done
