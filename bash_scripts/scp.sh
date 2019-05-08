#!/bin/bash

# Напишете shell script (който ще използвате от вашия линукс), който да приема параметър име на файл,
# който искате да копирате от os-server и да го копира в текущата директория (на вашия линукс).

if [[ $# -ne 1 ]]; then
	echo 'Missing argument'
	exit 1
else
	scp s62137@os-server.fmi.uni-sofia.bg:$1 $HOME
fi