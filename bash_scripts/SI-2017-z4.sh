# Напишете shell script, който получава задължителен първи позиционен параметър - директория и незадължителен втори - име на файл.
# Скриптът трябва да намира в подадената директория:

  #  броя на symlink-овете, чийто destination не съществува
  # Името на симлинка "->" името на destination, ако съществува

# Ако е подаден като аргумент файл - да се добавят в него, а ако не е - да се извеждат на екрана.

if [[ $# -eq 1 ]] && [[ -d $1 ]]; then
	symlinks=$(ls -la $1 | egrep '^l')
	broken_symlinks=$(find $1 -xtype l | awk -F"/" '{print $NF}')
	broken_symlinks_count=0
	while read -r link; do
		if [[ $(echo "$broken_symlinks" | grep $(echo "$link" | awk '{print $9}') | wc -l) -eq 0 ]]; then
			echo $(echo "$link" | awk '{print $9, $10, $11}')
		else
			broken_symlinks_count=$(( broken_symlinks_count+1 ))
		fi
	done < <(echo "$symlinks")
	echo "Broken symlinks: $broken_symlinks_count"
elif [[ $# -eq 2 ]] && [[ -d $1 ]]; then
	symlinks=$(ls -la $1 | egrep '^l')
	broken_symlinks=$(find $1 -xtype l | awk -F"/" '{print $NF}')
	broken_symlinks_count=0
	while read -r link; do
		if [[ $(echo "$broken_symlinks" | grep $(echo "$link" | awk '{print $9}') | wc -l) -eq 0 ]]; then
			echo $(echo "$link" | awk '{print $9, $10, $11}') >> $2
		else
			broken_symlinks_count=$(( broken_symlinks_count+1 ))
		fi
	done < <(echo "$symlinks")
	echo "Broken symlinks: $broken_symlinks_count" >> $2
else
	echo "Missing argument!"
	exit 1
fi
	