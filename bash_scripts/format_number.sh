#!/bin/bash

# Да се напише shell скрипт, който форматира големи числа, за да са по-лесни за четене.
# Като пръв аргумент на скрипта се подава цяло число.
# Като втори незадължителен аргумент се подава разделител. По подразбиране цифрите се разделят с празен интервал.

delimeter=" "
counter=0
if [[ $# -eq 1 ]] || [[ $# -eq 2 ]]; then
	number=$1
	number=$(echo $number | rev)
	nice_number=""
	if [[ $# -eq 2 ]]; then
		delimeter=$2
	fi
	for (( i=0; i<${#number}; i++)); do
		nice_number="$nice_number${number:$i:1}"
		counter=$((counter + 1))
 		if [[ $counter -eq 3 ]]; then
			nice_number="$nice_number$delimeter"
			counter=0
		fi
	done
	nice_number=$(echo $nice_number | rev)
	echo $nice_number
else
	echo 'script arguments count incorrect'
fi

