#!/bin/bash

# Да се напише shell скрипт, който приема параметър - име на потребител. 
# Скриптът да прекратява изпълненито на всички текущо работещи процеси на дадения потребител, и да извежда колко са били те.

if [[ $# -ne 1 ]]; then
	echo 'Expected username!'
	exit 1
else
	user=$1
	running_processes=$(ps -au${user} | awk '{print $1}')
	for process in $running_processes; do
		kill $process
	done
	echo "${#running_processes[@]} processes were killed for $user ...  "
fi

