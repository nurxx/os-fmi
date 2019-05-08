#!/bin/bash

# Приема произволен брой аргументи - имена на файлове или директории.
# Скриптът да извежда за всеки аргумент подходящо съобщение: - дали е файл, който може да прочетем 
#- ако е директория - имената на файловете в нея, които имат размер, по-малък от броя на файловете в директорията.

for elem in "$@"; do
	if [[ -d $elem ]]; then
		files=$(find $elem -type f 2>/dev/null)
		files_count=$(find $elem -type f 2>/dev/null | wc -l)

		for file in $files; do
			if [[ $(du $file | awk '{print $1}') -lt $files_count ]];then
				echo "$file"
			fi
		done

	elif [[ -f $elem ]] && [[ -r $elem ]]; then
		echo 'Permission given'
	elif [[ -f $elem ]] && [[ ! -r $elem ]]; then
		echo 'Permission denied'
	fi
done
