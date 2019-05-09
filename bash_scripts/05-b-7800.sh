#!/bin/bash

# Да се напише shell скрипт, който намира броя на изпълнимите файлове в PATH.


path=$(echo $PATH | tr ':' ' ')
count=0
for dir in $path; do
	files=$(find $dir -type f)
	for file in $files; do
		if [[ -x $file ]]; then
			echo "$file is executable"
			count=$((count + 1))
		fi
	done
done

echo "$count executable files in $PATH"

 