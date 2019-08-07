#!/bin/bash
# Да се напише shell скрипт, който проверява дали подаденият му параметър се състои само от букви и цифри.

if [[ $# -ne 1 ]] ; then
	echo 'Expected 1 script argument, but none was given'
	exit 1
else
	argument=$1
	[[ "$argument" =~ ^[[:alnum:]]*$ ]] && echo "is alphanumeric"
fi