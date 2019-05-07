#!/bin/bash

# Напишете shell script guess, която си намисля число, което вие трябва да познаeте. В зависимост от вашия отговор,
# програмата трябва да ви казва "надолу" или "нагоре",
# докато не познате числото. Когато го познаете, програмата да ви казва с колко опита сте успели.

rand_num=${RANDOM:0:2} # random number between 1-99, equivalent $(( (RANDOM % 99) + 1  ))
guess_times=0
while read user_guess
do
	guess_times=$(($guess_times+1))
	if [[ $user_guess -eq $rand_num ]]; then
		echo "Right! Guessed in $guess_times times."
		break;
	elif [[ $user_guess -lt $rand_num ]]; then
		echo "Bigger!"
	else
		echo "Smaller!"
	fi
done