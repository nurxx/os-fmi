#!/bin/bash

# Да се напише shell скрипт, който приканва потребителя да въведе низ - потребителско име на потребител от системата
# след което извежда на стандартния изход колко пъти потребителят се е логнал.

read -p 'Input username: ' username
logins=$(who | grep $username)
if [[ $? -eq 0 ]]; then
	logins=$( echo $logins | wc -l)
	echo "$username logged in $logins times"
else
	echo "$username has no logins so far"
fi