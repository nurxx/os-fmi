-- 04-a-5000

Намерете командите на 10-те най-стари процеси в системата.
- ` ps -ef --sort=start_time | head ` 

-- 04-a-6000

Намерете PID и командата на процеса, който заема най-много виртуална памет в системата.
- ` ps --sort=-pcpu | head -n 2 | awk -F" " '{print $1,$NF}' `

-- 04-b-5000

Намерете колко физическа памет заемат всички процеси на потребителската група SI.
- ` ps aux --Group SI | awk '{sum+=$5} END {print sum}' `

-- 04-b-7000

Намерете колко физическа памет заемат осреднено всички процеси на потребителската група SI. Внимавайте, когато групата няма нито един процес.
- ` ps aux --Group SI | awk '$5!=0 {sum+=$5} END {print sum/NR}' `

-- 04-b-8000

Намерете всички PID и техните команди (без аргументите), които нямат tty, което ги управлява. Изведете списък само с командите без повторения.
- ` ps aux | awk '($7=="?") {print $2,$11}' `

-- 04-b-9000

Да се отпечатат PID на всички процеси, които имат повече деца от родителския си процес.
