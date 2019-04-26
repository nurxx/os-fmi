#!/bin/bash
echo "$(cat text.txt)" > original.txt
echo "$(cat text.txt | tr -d [:punct:] | tr [:upper:] [:lower:] | sed 's/ /\n/g' | sort -u)" > text.txt
echo "$(agrep -v -w -f dic.txt text.txt)" > text.txt
while read word; do
	echo "$word:$(tre-agrep --best-match -s -w $word dic.txt| head -n 1)"
done < text.txt
echo "$(cat original.txt)" > text.txt
rm original.txt
