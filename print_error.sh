#!/bin/bash

cd ./test_source 

for file in $(ls *.cpp); do
	file_n=$(echo $file | sed s/[.]cpp//)
	cn=$(ls | grep -ce "^$file_n$")
	echo "$cn $file_n"
done

cd ..
