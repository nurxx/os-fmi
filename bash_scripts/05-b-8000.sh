#!/bin/bash

#  Напишете shell script, който получава като единствен аргумент име на потребител
#  и за всеки негов процес изписва съобщение за съотношението на RSS към VSZ. 
#  Съобщенията да са сортирани, като процесите с най-много заета виртуална памет са най-отгоре.

IFS='
' #setting IFS to newline

if [[ $# -ne 1 ]]; then
	echo "Expected 1 username!"
	exit 1
else
	user=$1
	processes="$(ps -aux | sort -nr -k5 | egrep "^${user}")"
	for process in $processes; do
		vsz=$(echo $process | awk '{print $5}')
		rsz=$(echo $process | awk '{print $6}')
		output=$(echo "scale=2; $rsz/$vsz" | bc)
		echo $output
	done
fi