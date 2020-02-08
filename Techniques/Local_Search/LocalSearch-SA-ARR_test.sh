#!/bin/bash

mkdir -p LocalSearch-SA-ARR_test

for f in ../../RefAssign-Instances/Instances/*.txt
do
	s=$(echo "$f" | cut -d'/' -f 5 | cut -d'.' -f 1)
	timeout 3m ./TestRALocalSearch.exe 	--main::instance $f \
										--main::method ARR_SA \
										--AddRemoveReferee_SimulatedAnnealing::start_temperature 1000.0 \
										--AddRemoveReferee_SimulatedAnnealing::min_temperature 1.0 \
										--AddRemoveReferee_SimulatedAnnealing::cooling_rate 0.999 \
										--AddRemoveReferee_SimulatedAnnealing::neighbors_sampled 500 \
										--AddRemoveReferee_SimulatedAnnealing::neighbors_accepted 50 \
										--main::output_file ./LocalSearch-SA-ARR_test/$s-result.txt
	echo "LocalSearch-SA-ARR: $s-result.txt"
done
