#!/bin/bash

mkdir -p Enumeration_test

for f in ../../RefAssign-Instances/Instances/*.txt
do
	s=$(echo "$f" | cut -d'/' -f 5 | cut -d'.' -f 1)
	timeout 3m ./TestRAEnumeration.exe $f 1 1 1 1 1 1 1 &> "./Enumeration_test/$s-result.txt"
	echo "Enumeration: $s-result.txt"
done
