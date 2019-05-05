#!/bin/bash
# Да се напише shell скрипт, който проверява дали подаденият му параметър се състои само от букви и цифри.

if [[ $# -ne 1 ]] ; then
	echo 'Expected 1 script argument, but none was given'
	exit 1
else
	file=$1
	non_matching=$(egrep '[^a-zA-Z0-9]' $file |wc -m)
	if [[ $non_matching -ne 0 ]]
	then
		echo 'File is not alphanumeric'
		exit 1
	else
		echo 'File is alphanumeric'
	fi
fi