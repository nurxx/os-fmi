#!/bin/bash

# Напишете скрипт, който ако се изпълнява от root потребителя:

# - извежда обобщена информация за
# броя и общото количество активна памет (RSS - resident set size, non-swaped
# physical memory that a task has used) на текущите процеси на всеки потребител

# - ако процесът с най-голяма активна памет на даден потребител използва два пъти
# повече памет от средното за потребителя, то скриптът да прекратява изпълнението
# му по подходящ начин.

if [[ $(whoami) -ne "root" ]]; then
	echo "User must be root!\n"
	exit 1
fi

users=$(ps aux | sed '1d' | awk '{print $1}' | sort -k1 | uniq)
users=(${users}) # convert to an array
for user in ${users[@]}; do
	echo "User: ${user} "
	user_processes=$(ps aux | awk -v user="${user}" '$1==user')
	user_proc_count=$(echo "${user_processes}" | wc -l)
	user_avg_rss=$(echo "${user_processes}"| awk '{sum+=$6; count++} END {print sum/count}')
	echo "${user_proc_count} processes running for ${user} ..."
	echo "Average RSS usage for ${user}: ${user_avg_rss}"

	proc_rss_greater_avg=$(echo "${user_processes}" | awk -v avg=${user_avg_rss} '$6 > avg')
	if [[ $proc_rss_greater_avg ]]; then
		while read -r proc; do
			pid=$(echo $proc | awk '{print $2}')
			rss=$(echo $proc | awk '{print $6}')
			echo "Process with pid : ${pid} user: ${user} will be killed ... "
			kill -SIGTERM $pid # terminates the process
		done< <(echo "$proc_rss_greater_avg")
	fi
done
