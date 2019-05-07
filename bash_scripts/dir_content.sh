#!/bin/bash

# Да се напише shell скрипт, който приканва потребителя да въведе пълното име на директория
# и извежда на стандартния изход подходящо съобщение за броя на всички файлове и директории в нея.

read -p 'Input directory name: ' directory

if [[ -d $directory ]]; then
	files_count=$(find $directory -type f 2>/dev/null | wc -l)
	dirs_count=$(find $directory -type d 2>/dev/null | wc -l)
	echo "$directory contains $dirs_count subdirectories and $files_count files"
else 
	echo "$directory doesn't exist"
	exit 1
fi