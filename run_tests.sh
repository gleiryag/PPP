#!/bin/bash


for file in $(ls test_source/*.cpp); do
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

echo $(date) >> errors

