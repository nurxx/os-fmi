#!/bin/bash

# Да се напише shell скрипт, който чете от стандартния вход имената на 3 файла, обединява редовете на първите два,
# подрежда ги по азбучен ред и резултата записва в третия файл.

if [[ $# -ne 3 ]]; then
	echo 'Arguments count must be 3'
else
	file1=$1
	file2=$2
	output=$3
	cmd=$(cat $file1 $file2 | sort > $output)
	echo 'result saved in $output'
fi