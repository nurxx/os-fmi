#!/bin/bash

# 	Напишете скрипт, който приема задължителен позиционен аргумент - име на потребител (FOO).
# 	Ако скриптът се изпълнява от root:
# 	a) да извежда имената на потребителите, които имат повече на брой процеси от FOO, ако има такива;
# 	б) да извежда средното време (в секунди), за което са работили процесите на всички потребители на системата (TIME);
# 	в) ако съществуват процеси на FOO, които са работили над два пъти от средното време,
# 	скриптът да прекратява изпълнението им пo подходящ начин

if [[ "$(whoami)" != "root" ]];then
	echo "Root expected!"
	exit 1
fi

if [[ $# -ne 1 ]]; then
	echo "Missing argument!"
	exit 2
fi

foo=$1
foo_processes=$(ps aux | sed '1d' | awk -v user="$foo" '$1 == user' | wc -l)
all_users=$(ps aux | sed '1d' | awk '{print $1}' | sort | uniq)
while read -r user; do
	if [[ "$user" != "$foo" ]]; then
		user_processes=$(ps aux | sed '1d' | awk -v user="$user" '$1 == user' | wc -l)
		if [[ $user_processes -gt $foo_processes ]]; then
			echo -e "$user has more processes running than $foo"
		fi
	fi
done < <(echo "$all_users") 

avg_time_all_minutes=$(ps aux | sed '1d' | awk '{print $10}' | awk -F":" '{sum+=$2; sum+=$1*60} END {print sum}')
echo "Average time for all processes running : $avg_time_all_minutes minutes"
foo_processes=$(ps -aux | sed '1d' | awk -v user="$foo" '$1 == user' | awk '{print $10}' | awk -F":" '{sum+=$2; sum+=$1*60} END {print sum}')
running_processes=$(ps -aux | sed '1d')
while read -r process; do
	if [[ $(echo "$process" |awk '{print $10}' | awk -F":" '{sum+=$2; sum+=$1*60} END {print sum}') -gt $(echo "$avg_time_all_minutes*2" | bc) ]]; then
		process_id=$( echo "$process" | awk '{print $2}')
		echo "Process with pid: $process_id was terminated due to exceeding average running time (x2)"
		# kill -SIGTERM $process_id - terminate the process 
	fi
done< <(echo "$running_processes")



