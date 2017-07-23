#!/bin/bash


for file in $(ls test_source/*.cpp); do
        to_run=./$(echo $file | sed s/[.]cpp//)
	$to_run
done

