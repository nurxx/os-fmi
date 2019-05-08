#!/bin/bash

# Да се напише shell скрипт, който приема два параметъра - име на директория и число.
# Скриптът да извежда на стандартния изход имената на всички обикновени файлове във директорията,
# които имат размер, по-голям от подаденото число.

dir_path=$1
max_size=$2

if [[ -d $dir_path ]]; then
	files=$(find $dir_path -maxdepth 1 -type f)
	for file in $files; do
		file_size=$(du $file | awk '{print $1}' )
		if [[ $file_size -gt $max_size ]]; then
			echo "$file"
		fi
	done
else
	echo "$dir_path not found"
	exit 1
fi