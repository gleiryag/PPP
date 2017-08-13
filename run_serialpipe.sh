#!/bin/bash

test_names=("w2" "w6" "w10")
test=$1


if [ $test != '' ]
then
	test_names=($test)
fi


for name in "${test_names[@]}"
do
	to_run="./test_source/test_5__i5_s5_"$name"_1_1_1_1_1_pipeline_"
	echo "Running test $to_run"
	$to_run
	status_code=$?
	if [ $status_code != '0' ] 
        then
		echo "status_code $status_code $to_run" >> errors
	else 
		echo "$to_run" >> pass
	fi	

	tar czf "pipe_$name-$(date '+%d-%H-%M-%S').tar.gz" "test_results"

	rm ./test_results/*
done

echo $(date) >> errors

