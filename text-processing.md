-- 03-a-0200

Сортирайте /etc/passwd лексикографски по поле UserID. 
`cat /etc/passwd | sort -t: -k3`


-- 03-a-0201

Сортирайте /etc/passwd числово по поле UserID.
` cat /etc/passwd | sort -n -t: -k3`
(Открийте разликите с лексикографската сортировка)

-- 03-a-0210

Изведете само 1-ва и 5-та колона на файла /etc/passwd спрямо разделител ":".
`cat /etc/passwd | cut -d: -f1,5`

-- 03-a-0211

Изведете съдържанието на файла /etc/passwd от 2-ри до 6-ти символ.
 `cat /etc/passwd | cut -c2-6` 
 `cut -c 2-6 /etc/passwd`
-- 03-a-1500

Намерете броя на символите в /etc/passwd. А колко реда има в /etc/passwd?
 `cat /etc/passwd | wc -m` 
 `cat /etc/passwd | wc -l`

-- 03-a-2000

Извадете от файл /etc/passwd:
- първите 12 реда - `cat /etc/passwd | head -n 12`
- първите 26 символа - `cat /etc/passwd | head -c 26`
- всички редове, освен последните 4 - `cat /etc/passwd | head -n -4`
- последните 17 реда - `cat /etc/passwd | tail -n 17`
- 151-я ред (или друг произволен, ако нямате достатъчно редове) - `sed -n 151p /etc/passwd`
- последните 4 символа от 13-ти ред - `sed -n 13p /etc/passwd | tail -c 4`

-- 03-a-2100

Отпечатайте потребителските имена и техните home директории от /etc/passwd.
 `cat /etc/passwd | cut -d: -f1,6`

-- 03-a-2110cat 

Отпечатайте втората колона на /etc/passwd, разделена спрямо символ '/'.
 `cat /etc/passwd | cut -d/ -f2`

-- 03-a-3000

Запаметете във файл в своята home директория резултатът от командата ls -l изпълнена за вашата home директорията.
Сортирайте създадения файла по второ поле (numeric, alphabetically).
 `ls -l | sort -n -k 2 > content.txt`

-- 03-a-5000

Отпечатайте 2 реда над вашия ред в /etc/passwd и 3 реда под него // може да стане и без пайпове
 `grep '62137' -A3 -B2 /etc/passwd`

-- 03-a-5001

Колко хора не се казват Ivan според /etc/passwd
 `grep -v 'Ivan' /etc/passwd | wc -l`

-- 03-a-5002

Изведете имената на хората с второ име по-дълго от 7 (>7) символа според /etc/passwd
 `cat /etc/passwd | awk -F":" '{print $5}' | awk -F"," '{print $1}' | awk 'length($2)>7 {print $1}'`


-- 03-a-5003

Изведете имената на хората с второ име по-късо от 8 (<=7) символа според /etc/passwd // !(>7) = ?
 `cat /etc/passwd | awk -F":" '{print $5}' | cut -d, -f1 | awk 'length($2) < 8 {print $1}'`

-- 03-a-5004

Изведете целите редове от /etc/passwd за хората от 03-a-5003

-- 03-b-0300

Намерете факултетния си номер във файлa /etc/passwd.
 `cat /etc/passwd | egrep --color "62137"`

-- 03-b-3000

Запазете само потребителските имена от /etc/passwd във файл users във вашата home директория.
 `cat /etc/passwd | cut -d: -f1 > $HOME/users`

-- 03-b-3400

Колко коментара има във файла /etc/services ? Коментарите се маркират със символа #, след който всеки символ на реда се счита за коментар.
 `cat /etc/services | cut -d '#' -f 2 | wc -m`


-- 03-b-3450

Вижте man 5 services. Напишете команда, която ви дава името на протокол с порт естествено число N. Командата да не отпечатва нищо, ако търсения порт не съществува (например при порт 1337). Примерно, ако номера на порта N е 69, командата трябва да отпечати tftp.
 `grep -w '69' /etc/services`  or `cat /etc/services | egrep --color "\<69\>"`


-- 03-b-3500

Колко файлове в /bin са shell script? (Колко файлове в дадена директория са ASCII text?)
 `[s62137@os-server bin]$ find . -type f | grep '*.sh' | wc -l`

-- 03-b-3600

Направете списък с директориите на вашата файлова система, до които нямате достъп. Понеже файловата система може да е много голяма, търсете до 3 нива на дълбочина. А до кои директории имате достъп? Колко на брой са директориите, до които нямате достъп?
 `find / -maxdepth 3 -type d -perm -u=--- | wc -l`
 `find / -maxdepth 3 -type d ! -readble`
 `find / -maxdepth 3 -type d -perm -u=rwx | wc -l` - accesible 

-- 03-b-4000

Създайте следната файлова йерархия.
/home/s...../dir1/file1
/home/s...../dir1/file2
/home/s...../dir1/file3

Посредством vi въведете следното съдържание:
file1:
1
2
3

file2:
s
a
d
f

file3:
3
2
1
45
42
14
1
52cat 

Изведете на екрана:
	* статистика за броя редове, думи и символи за всеки един файл
	* статистика за броя редове и символи за всички файлове
	* общия брой редове на трите файла

-- 03-b-4001

Във file2 подменете всички малки букви с главни.
 `echo "$(cat file2 | tr [:lower:] [:upper:])" > file2`

-- 03-b-4002

Във file3 изтрийте всички "1"-ци.
 `sed -i 's/1//g' file3 `

-- 03-b-4003

Изведете статистика за най-често срещаните символи в трите файла.
 `cat file1 file2 file3 | fold -w1 | sort -n | uniq -c | sort -rn -k1 | head -n1`

-- 03-b-4004

Направете нов файл с име по ваш избор, който е конкатенация от file{1,2,3}.
Забележка: съществува решение с едно извикване на определена програма - опитайте да решите задачата чрез него.
 `cat file1 file2 file3 > all_files.txt`

-- 03-b-4005

Прочетете текстов файл file1 и направете всички главни букви малки като запишете резултата във file2.
 `echo "$(cat file1 | tr [:upper:] [:lower:])" > file2`

-- 03-b-5200

Изтрийте всички срещания на буквата 'a' (lower case) в /etc/passwd и намерете броят на оставащите символи.
 `sed -i 's/a//g' /etc/passwd | wc- m`

-- 03-b-5300

Намерете броя на уникалните символи, използвани в имената на потребителите от /etc/passwd.
 `cat /etc/passwd | cut -d: -f1 | fold -w1 | sort -u | wc -l`

-- 03-b-5400

Отпечатайте всички редове на файла /etc/passwd, които не съдържат символния низ 'ov'.
 `cat passwd | grep -v 'ov'`

-- 03-b-6100

Отпечатайте последната цифра на UID на всички редове между 28-ми и 46-ред в /etc/passwd.
 `cut -d: -f3 /etc/passwd | sed -n 28,46p | rev | cut -c 1`

-- 03-b-6700

Отпечатайте правата (permissions) и имената на всички файлове, до които имате read достъп, намиращи се в директорията /tmp.
 `find /tmp -perm /u=r 2>/dev/null -exec stat --format "%n %A" {} \;`

-- 03-b-6900

Намерете имената на 10-те файла във вашата home директория, чието съдържание е редактирано най-скоро. На първо място трябва да бъде най-скоро редактираният файл. Намерете 10-те най-скоро достъпени файлове. (hint: Unix time)
 `find $HOME -type f -exec stat --format "%n %Y" {} \; | sort -t' ' -n -k2 | awk '{print $1}'| head -n5`


-- 03-b-7000

Файловете, които съдържат C код, завършват на `.c`.
Колко на брой са те във файловата система (или в избрана директория)?
Колко реда C код има в тези файлове?
- `find . -type f -name "*.c" | wc -l`
- `find . -type f -name "*.c" -exec cat {} \; | wc -m`

-- 03-b-7500

Даден ви е ASCII текстов файл (например /etc/services). Отпечатайте хистограма на N-те (например 10) най-често срещани думи.
 `cat /etc/services | cut -f1 | uniq -c | sort -r -n -t " " -k 1 | head -n 10`


-- 03-b-8000

Вземете факултетните номера на студентите от СИ и ги запишете във файл si.txt сортирани.
 `cat passwd | grep 'SI' | cut -d: -f1 | sed 's/s//g' | sort -n > $HOME/si.txt`

-- 03-b-8500

За всеки логнат потребител изпишете "Hello, потребител", като ако това е вашият потребител, напишете "Hello, потребител - this is me!".

Пример:

hello, human - this is me!
Hello, s63465
Hello, s64898

-- 03-b-8520

Изпишете имената на студентите от /etc/passwd с главни букви.
 `cat passwd | awk" '{print $5}' | cut -d, -f1 | tr '[:lower:]' '[:upper:]'`


-- 03-b-8600

Shell Script-овете са файлове, които по конвенция имат разширение .sh. Всеки такъв файл започва с "#!<interpreter>" , където <interpreter> указва на операционната система какъв интерпретатор да пусне (пр: "#!/bin/bash", "#!/usr/bin/python3 -u"). 

Намерете всички .sh файлове и проверете кой е най-често използваният интерпретатор.

 `find / -type f -name "*.sh" -exec cat {} \; | grep "^#!" | sed 's/#!//g' | sort | uniq -c | sort -rn |head -n 1 | cut -f2`

-- 03-b-8700

Намерете 5-те най-големи групи подредени по броя на потребителите в тях.
 `find . -type f -exec stat --format "%G" {} \; | sort | uniq -c | head -n 5 | awk '{print $2}'`

-- 03-b-9000

Направете файл eternity. Намерете всички файлове, които са били модифицирани в последните 15мин (по възможност изключете .).  Запишете във eternity името на файла и часa на последната промяна.
 `find $HOME -type f -mmin -15 -exec stat --format "%n %y" {} \; | awk '{print $1,$3}' | sed -e "s/\(\.[[:digit:]]*$\)//g" > eternity` 

-- 03-b-9050

Копирайте файл /home/tony/population.csv във вашата home директория.
 `cp /home/tony/population.csv ~`

-- 03-b-9051

Използвайки файл population.csv, намерете колко е общото население на света през 2008 година. А през 2016?
 `cat population.csv | egrep --color "2008" | egrep --color -o "[[:digit:]]+$"| awk '{sum += $1} END {print sum}'`
 `cat population.csv | egrep --color "2008" | awk -F"," '{sum+=$NF} END {print sum}'`


-- 03-b-9052

Използвайки файл population.csv, намерете през коя година в България има най-много население.
 `egrep --color "Bulgaria" population.csv | tr "," " " | sort -rn -k4 | head -n1`


-- 03-b-9053

Използвайки файл population.csv, намерете коя държава има най-много население през 2016. А коя е с най-малко население?
(Hint: Погледнете имената на държавите)
 `cat population.csv | egrep --color "2016" | awk -F"," '{if($NF > max) max=$NF} END {print $1}'`

-- 03-b-9054

Използвайки файл population.csv, намерете коя държава е на 42-ро място по население през 1969. Колко е населението й през тази година?
 `cat population.csv | egrep --color "1969" | egrep --color -o "^\".*\"|^[[:alpha:]]*" > countries
  cat population.csv | egrep --color "1969" | egrep --color "^\".*\"|^[[:alpha:]]*" | awk -F, '{print $NF}' > ppl
  paste ppl countries | sort -t" " -n -r -k1 | sed -n "42p" | awk '{print $2}'`
  

-- 03-b-9100

В home директорията си изпълнете командата `curl -o songs.tar.gz "http://fangorn.uni-sofia.bg/misc/songs.tar.gz"`

-- 03-b-9101

Да се разархивира архивът songs.tar.gz в папка songs във вашата home директорията.
 `tar -xvzf songs.tar.gz`

-- 03-b-9102

Да се изведат само имената на песните.
 `tar -tf songs.tar.gz | cut -d"-" -f2 | cut -d"(" -f1 `

-- 03-b-9103

Имената на песните да се направят с малки букви, да се заменят спейсовете с долни черти и да се сортират.
 `tar -tf songs.tar.gz | cut -d"-" -f2 | cut -d"(" -f1 | tr [:upper:] [:lower:] | sed 's/ //' | sed 's/ /_/g' | sort` 


-- 03-b-9104

Да се изведат всички албуми, сортирани по година.

-- 03-b-9105

Да се преброят/изведат само песните на Beatles и Pink.
 `tar -tf songs.tar.gz | egrep --color "Pink|Beatles" | wc -l`

-- 03-b-9106

Да се направят директории с имената на уникалните групи. За улеснение, имената от две думи да се напишат слято:
Beatles, PinkFloyd, Madness

-- 03-b-9200

Напишете серия от команди, които извеждат детайли за файловете и директориите в текущата директория, които имат същите права за достъп както най-големият файл в /etc директорията.
 `find . -type f -perm $(find /etc -type f -exec stat --format "%s %n %a" {} \; 2>/dev/null | sort -t" " -n -r | head -n 1 |awk '{print $3}')`


-- 03-b-9300

Дадени са ви 2 списъка с email адреси - първият има 12 валидни адреса, а вторията има само невалидни. Филтрирайте всички адреси, така че да останат само валидните. Колко кратък регулярен израз можете да направите за целта?

Валидни email адреси (12 на брой):
email@example.com
firstname.lastname@example.com
email@subdomain.example.com
email@123.123.123.123
1234567890@example.com
email@example-one.com
_______@example.com
email@example.name
email@example.museum
email@example.co.jp
firstname-lastname@example.com
unusually.long.long.name@example.com

Невалидни email адреси:
#@%^%#$@#$@#.com
@example.com
myemail
Joe Smith <email@example.com>
email.example.com
email@example@example.com
.email@example.com
email.@example.com
email..email@example.com
email@-example.com
email@example..com
Abc..123@example.com
(),:;<>[\]@example.com
just"not"right@example.com
this\ is"really"not\allowed@example.com

-- 03-b-9500

Запишете във файл next потребителското име на човека, който е след вас в изхода на who. Намерете в /etc/passwd допълнителната ифнромация (име, специалност...) и също го запишете във файла next. Използвайки файла, изпратете му съобщение "I know who you are, информацията за студента"

Hint: можете да използвате командата expr, за да смятате аритметични изрази. Например, ще получим 13, ако изпълним: expr 10 + 3

Бонус: "I know who you are, само името му"


