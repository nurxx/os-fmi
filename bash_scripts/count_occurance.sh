 #!/bin/bash

# Приема произволен брой аргументи - имена на файлове. Скриптът да прочита от стандартния вход символен низ
# и за всеки от зададените файлове извежда по подходящ начин на стандартния изход броя на редовете, които съдържат низа.

read -p 'string: ' string 
for file in "$@"
do
	occurance_count=$(grep $string $file | wc -l)
	echo "Occurs $occurance_count times in $file."
done