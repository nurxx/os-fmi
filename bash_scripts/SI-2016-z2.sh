#!/bin/bash

IFS='
'
if [[ $# -ne 1 ]]; then
	echo "Missing argument!"
	exit 1
else
	max_rss=$1
	if [[ $(whoami) = "root" ]]; then
		users=$(ps -e -o uid,pid,rss | sed '1d' | awk '{print $1}' | sort -nk1 | uniq)
		users=(${users})
		for user in "${users[@]}"; do
			echo "User id : $user"
			processes=$(ps -e -o uid,pid,rss | egrep "^.*$user" | sort -nr -k3)
			processes=(${processes})
			echo ${processes[0]} 
			max_pid=$(echo ${processes[0]} | awk '{print $2}')
			echo $max_pid
			total_rss=0
			for process in "${processes[@]}"; do
				rss=$(echo $process | awk '{print $3}')
				total_rss=$(echo "${total_rss}+${rss}" | bc)
			done
			echo "Total rss for $user -> ${total_rss}"
			if [[ $total_rss -gt $max_rss ]]; then
				echo "Signaling to stop process with PID: ${max_pid}" 
				# kill -SIGSTOP $max_pid 
			fi
		done
	fi
fi
