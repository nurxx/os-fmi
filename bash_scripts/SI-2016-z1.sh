#!/bin/bash

if [[ $# -ne 1 ]]; then
	echo "Missing argument!"
	exit 1
elif [[ -d $1 ]]; then
	broken_symlinks=$(find $1 -type l | xargs file | grep "broken" | awk '{print $1}')
	broken_symlinks=(${broken_symlinks}) # assign to an array with values in variable 
	for link in "${broken_symlinks[@]}"; do
		echo "${link} is a broken symbolic link"
	done
	echo "Total ${#broken_symlinks[@]}"
fi