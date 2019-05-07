#!/bin/bash
# Да се напише shell скрипт, който чете от стандартния вход име на файл и символен низ,
# проверява дали низа се съдържа във файла и извежда на стандартния изход кода на завършване на командата.

read -p "File: " filename
read -p "Word: " string

cmd=$(find $HOME -name $filename -exec grep $string {} \;)
if [[ $? -eq 0 ]]; then
	echo "Exists"
else
	echo "Doesn't exist"
fi
echo $?




