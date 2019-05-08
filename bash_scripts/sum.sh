#!/bin/bash

# Да се напише shell скрипт, който приема два параметъра - име на директория и число.
# Скриптът да извежда сумата от размерите на файловете в директорията, които имат размер, по-голям от подаденото число.

dir_path=$1
number=$2
sum=0
if [[ ! -d $dir_path ]]; then
	echo "$dir_path not found"
	exit 1
else
	files=$(find $dir_path -maxdepth 1 -type f)
	for file in $files; do
		file_size=$(du $file | awk '{print $1}')
		echo $file_size
		if [[ $file_size -gt $number ]]; then
			sum=$((sum + $file_size))
		fi
	done
	echo "Sum of files with size bigger than $number : $sum"
fi