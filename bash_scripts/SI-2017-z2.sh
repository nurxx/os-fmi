#!/bin/bash

if [[ $(whoami) != "root" ]]; then
	echo "Only root!"
	exit 10
fi

if [[ $# -ne 3 ]]; then
	echo "Expected exactly 3 arguments!"
	exit 1
else
	SRC=$1
	DST=$2
	ABC=$3
	if [[ ! -d $SRC ]]; then
		echo "$SRC is not a directory"
		exit 2
	fi

	if [[ ! -d $DST ]];then
		echo "$DST is not an empty directory"
		exit 3
	fi

	files=$(find $SRC -name "*${ABC}*" -type f 2>/dev/null)
	if ! [[ $files ]];then 
		echo "No file names containing $ABC"
		exit 5
	fi

	files=(${files})

	for file in "${files[@]}";do
			len="$SRC"
			len=$(echo ${#SRC})
			path=$(echo $file | cut -c $len- | grep -o "/.*/" | cut -c 2-)
			echo $path
			if [[ ! -e $path ]];then
				mkdir -p ${DST}${path}
			fi
			mv $file ${DST}${path}
	done
fi

