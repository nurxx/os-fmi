#!/bin/bash

# Имате компилируем (a.k.a няма синтактични грешки) source file на езика C.
# Напишете shell script, който да покзва колко е дълбоко най-дълбокото nest-ване (влагане).

if [[ $# -ne 1 ]]; then
	echo "Missing argument"
	exit 1
else
	current_depth=0
	max_depth=0
	file=$(cat $1)
	for (( i=0; i<${#file};i++ )); do
		char="${file:$i:1}"
		max_depth=$(( $max_depth > current_depth ? $max_depth : $current_depth ))

		if [[ $char = "{" ]];then
			current_depth=$((current_depth+1))
		fi

		if [[ $char = "}" ]]; then
			current_depth=$((current_depth-1))
		fi
	done
	echo $max_depth
fi