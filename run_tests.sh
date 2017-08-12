#!/bin/bash

test_names=("w2" "w6" "w10")
for name in "${test_names[@]}"
do
	for file in $(ls test_source/*$name*.cpp); do
        	to_run=./$(echo $file | sed s/[.]cpp//)
		echo "Running test $to_run"
		$to_run
		status_code=$?
		if [ $status_code != '0' ] 
        	then
			echo "status_code $status_code $to_run" >> errors
		else 
			echo "$to_run" >> pass
		fi	
	done
	tar czf "test_results_$name-$(date '+%d-%H-%M-%S').tar.gz" "test_results" 
	rm "test_results/*"
done

echo $(date) >> errors

