#!/bin/bash

# Да се напише shell скрипт, който приема файл и директория. Скриптът проверява в подадената директория и 
# нейните под-директории дали съществува копие на подадения файл и отпечатва имената на намерените копия,
# ако съществуват такива.

if [[ ! -f $1 ]] || [[ ! -d $2 ]]; then
	echo "Incorrect argument type"
else
	filename=$1
	dir_path=$2
	files=$(find $dir_path -type f)
	for file in $files; do
		if [[ $(md5sum $filename | awk '{print $1}') = $(md5sum $file | awk '{print $1}') ]] && [[ $filename != $file ]]; then
			echo "$file"
		fi
	done
fi

