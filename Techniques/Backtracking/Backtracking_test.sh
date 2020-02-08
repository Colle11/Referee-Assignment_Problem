#!/bin/bash

mkdir -p Backtracking_test

for f in ../../RefAssign-Instances/Instances/*.txt
do
	s=$(echo "$f" | cut -d'/' -f 5 | cut -d'.' -f 1)
	timeout 3m ./TestRABacktracking.exe $f 1 1 1 1 1 1 1 &> "./Backtracking_test/$s-result.txt"
	echo "Backtracking: $s-result.txt"
done
