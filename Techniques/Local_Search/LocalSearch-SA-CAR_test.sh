#!/bin/bash

mkdir -p LocalSearch-SA-CAR_test

for f in ../../RefAssign-Instances/Instances/*.txt
do
	s=$(echo "$f" | cut -d'/' -f 5 | cut -d'.' -f 1)
	timeout 3m ./TestRALocalSearch.exe 	--main::instance $f \
										--main::method CAR_SA \
										--ChangeAssignedReferees_SimulatedAnnealing::start_temperature 1000.0 \
										--ChangeAssignedReferees_SimulatedAnnealing::min_temperature 1.0 \
										--ChangeAssignedReferees_SimulatedAnnealing::cooling_rate 0.999 \
										--ChangeAssignedReferees_SimulatedAnnealing::neighbors_sampled 500 \
										--ChangeAssignedReferees_SimulatedAnnealing::neighbors_accepted 50 \
										--main::output_file ./LocalSearch-SA-CAR_test/$s-result.txt
	echo "LocalSearch-SA-CAR: $s-result.txt"
done
