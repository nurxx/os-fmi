#!/bin/bash

# Да се напише shell скрипт, който валидира дали дадено цяло число попада в целочислен интервал.
# Скриптът приема 3 аргумента: числото, което трябва да се провери; лява граница на интервала; дясна граница на интервала.
# Скриптът да връща exit status:
# - 3, когато поне един от трите аргумента не е цяло число
# - 2, когато границите на интервала са обърнати
# - 1, когато числото не попада в интервала
# - 0, когато числото попада в интервала

# Примери:
# $ ./validint.sh -42 0 102; echo $?
# 1

# $ ./validint.sh 88 94 280; echo $?
# 1

# $ ./validint.sh 32 42 0; echo $?
# 2

# $ ./validint.sh asdf - 280; echo $?
# 3

if [[ $# -ne 3 ]]; then
	echo "Arguments count must be 3"
	exit 1
fi

for elem in "$@"; do
	echo $elem
	if ! [[ "$elem" =~ [-]?[0-9]+ ]]; then
		exit 3
	fi
done

check_number=$1
leftborder=$2
rigthborder=$3

if [[ $leftborder -gt $rigthborder ]]; then
	exit 2
elif [[ $check_number -gt $rigthborder ]] || [[ $check_number -lt $leftborder ]]; then
	exit 1
else
	exit 0
fi
