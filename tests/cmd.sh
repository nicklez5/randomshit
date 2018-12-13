#!/bin/sh
INPUTS=("echo hello;" "echo hello world;" "ls -l")

for input in "${INPUTS[@]}"
do 
	echo "./test_cmd ${input}"
	./test_cmd ${input}
done

