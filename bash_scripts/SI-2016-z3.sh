#!/bin/bash

IFS='
'
if [[ $(whoami) != "ilknur" ]]; then
	echo "User must be root!"
	exit 1
fi 

cat /etc/passwd | awk -F":" '{print $6}' | egrep "home" > homedirs
users=$(cat /etc/passwd | awk -F":" '{print $1}')
users=(${users})
for user in "${users[@]}"; do
	do_exist=$(egrep "^/home/.*${user}" homedirs 2>/dev/null| head -n1 )
	echo "$do_exist"
	if [[ $do_exist ]];then
		echo "Homedir for $user exists!"
		if [[ -w $do_exist ]]; then
			echo "$user can write in their homedir"
		else 
			echo "$user cannot write in  their homedir"
		fi
	else
		echo "Homedir for $user doesn't exist!"
	fi
done