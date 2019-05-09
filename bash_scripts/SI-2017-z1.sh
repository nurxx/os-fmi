#!/bin/bash

if [[ $# -lt 1 ]]; then
	echo "Missing arguments!"
	exit 1
elif [[ $# -eq 1 ]]; then
	if [[ ! -d $1 ]]; then
		echo "First argument expected to be directory name"
		exit 2
	fi
	echo "Listing broken symlinks ... "
	broken_symlinks=$(find $1 -type l -xtype l)
	broken_symlinks=(${broken_symlinks})
	for link in "${broken_symlinks[@]}"; do 
		echo "$link is a broken symlink"
	done
elif [[ $# -eq 2 ]]; then
	dir=$1
	max_count=$2
	files=$(find $dir -type f)
	files=(${files})
	for file in "$files"; do
		hardlinks=$(find $dir -samefile $file | wc -l)
		if [[ $hardlinks -ge $max_count ]]; then
			echo "$file 	hardlinks: $hardlinks"
		fi
	done	
fi
