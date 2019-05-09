#!/bin/bash

# Напишете shell script, който да приема параметър име на директория, 
# от която взимаме файлове, и опционално експлицитно име на директория, в която ще копираме файлове. 
# Скриптът да копира файловете със съдържание, променено преди по-малко от 45 мин, от първата директория във втората директория.
# Ако втората директория не е подадена по име, нека да получи такова от днешната дата във формат, който ви е удобен.
# При желание новосъздадената директория да се архивира.

if [[ $# -lt 1 ]]; then 
	echo "You should pass at least 1 argument"
	exit 1
elif [[ $# -eq 1 ]]; then
	src=$1
	dest=$(date "+%F")
	dest="$HOME/${dest}"
	mkdir -p $dest
elif [[ $# -eq 2 ]]; then 
	src=$1
	dest=$2
	if [[ ! -d $dest ]]; then
		echo "Expected destination directory. $2 is not a directory!"
		exit 1
	fi
fi

find $src -type f -mmin -45 -exec cp '{}' $dest \;
if [[ $? -eq 0 ]]; then
	echo "Some files from $src were copied to $dest."
fi

echo "Do you want to archive $dest ?(y/n)"
read choice

if [[ $choice = "y" ]]; then
	echo "Archiving directory ..."
	tar cvzf ${dest}.tar.gz ${dest}
	echo "Done!"
fi

