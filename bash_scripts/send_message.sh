#!/bin/bash

# Напишете shell script, който по подаден като аргумент файл с map между <nickname> -> <реален username в os-server> и nickname, ще ви улесни да изпращате съобщения на хората.

# Пример за файл указател:
# tinko		s61966
# minko		s881234
# ginko		s62000
# dinko		s77777
# senpai 	velin

if [[ ! -f $1 ]]; then
	echo "First argumnet must be a file"
elif [[ $# -lt 2 ]] || [[ $# -gt 2 ]]; then
	echo "Arguments count must be 2"
else
	receiver=$(grep "$2" $1 | awk '{print $2}')
	if [[ $? -eq 0 ]]; then
		echo "Hello, $2!" | write $receiver
	else
		echo "contact with username:$2 not found"
	fi 
fi