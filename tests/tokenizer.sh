#!/bin/sh
INPUTS=("echo hello" "ls #-l" "git status" "exit")

for input in "${INPUTS[@]}"
do
	echo "./tokenizer ${input}"
	output=$(./tokenizer ${input})
	echo "Output: \"${output}\""
	echo "Input: \"${input}\""
	if [ "${output}" = "${input}" ]
	then
		echo "Test passed"
	else
		echo "Test failed"
	fi
done

