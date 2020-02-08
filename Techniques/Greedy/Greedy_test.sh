#!/bin/bash

mkdir -p Greedy_test

for f in ../../RefAssign-Instances/Instances/*.txt
do
	s=$(echo "$f" | cut -d'/' -f 5 | cut -d'.' -f 1)
	timeout 3m ./RA_Driver.exe $f 1 1 1 1 1 1 1 &> "./Greedy_test/$s-result.txt"
	echo "Greedy: $s-result.txt"
done
