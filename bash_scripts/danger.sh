#!/bin/bash

# Да се напише shell скрипт, който извежда на стандартния изход факултетния номер на потребителя,
# който изпълнява скрипта, или казва "DANGER! It's a teacher!", ако потребителското име не е факултетен номер.

user=$(whoami)
if [[ "$user" =~ "^s[0-9]{5,6}$" ]]; then
	echo $user
else
	echo "DANGER! It's a teacher!"
fi