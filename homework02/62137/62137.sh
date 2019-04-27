#!/bin/bash

if [[ $# -ne 4 ]]
then
	echo "Not enough arguments passed to the script!"
	exit 1
fi

LOG_FILE=$1
EEG_FILE=$2
WAV_FILE=$3
OUTPUT_DIR=$4

if [[ ${LOG_FILE: -4} != ".log" || ${EEG_FILE: -4} != ".xml" || ${WAV_FILE: -4} != ".wav" ]]
then
	echo "Incorrect file type!"
	exit 1
fi

echo "$(cat $EEG_FILE | egrep "tick")" > ticks 
duplicates=$(sort $LOG_FILE| uniq --count --repeated | wc -l)
if [[ $duplicates -ne 0 ]]
then
	echo "$LOG_FILE contains duplicate stimuls!"
	exit 1
fi

echo $EEG_TZ
mkdir -p $OUTPUT_DIR 

rate=$(cat $EEG_FILE | egrep "SamplingRate" | tr -d "a-zA-Z></")
start_recording_date=$(cat $EEG_FILE | egrep "StartRecordingDate" | tr -d "a-zA-Z></" | awk -F"." '{print $3,$2,$1}' | tr " " "-")
echo $start_recording_date
start_recording_time=$(cat $EEG_FILE | egrep "StartRecordingTime" | tr -d "a-zA-Z></")
echo $start_recording_time
duration=$(cat $EEG_FILE | egrep "RecordLength" | tr -d "a-zA-Z></" | awk -F: '{ print ($1 * 3600) + ($2 * 60) + $3 }')

if [[ $EEG_TZ != " " ]]
then
	eeg_start=$(TZ=":$EEG_TZ" date --date="$start_recording_date $start_recording_time" "+%s")
	echo $eeg_start
else
	eeg_start=$(TZ="UTC" date --date="$start_recording_date $start_recording_time" "+%s")
	echo $eeg_start
fi

eeg_end=$(($eeg_start + $duration))
min=0.2
from_line=1
current_index=0

while read p
do
	stimul=$(echo ${p} | awk '{print $1}')
	if [ "$stimul" = "beep" ]
	then
		wav_start=$(echo ${p} | awk '{print $3}')
	fi
	stimul_start=$(echo ${p} | awk '{print $2}')
	stimul_end=$(echo ${p} | awk '{print $3}')
	stimul_duration=$(echo ${p} |awk '{print $3-$2}')

	if [ $(echo "$stimul_duration < $min" | bc) -eq 1 ]
	then
		echo "$stimul less than $min sec was skipped!"

	elif [[ $(echo "$stimul_start > $eeg_end" | bc) -eq 1 || $(echo "$stimul_end > $eeg_end" | bc) -eq 1 ]]
	then 
		echo "$stimul out of time range was skipped!"

	elif [ "$stimul" != "beep" ]
	then
		to_line=$(echo $rate*$stimul_duration | bc)
		to_line=${to_line%.*} 
		to_line=$(($to_line + $current_index))
		current_index=$to_line 
		sed -n "$from_line, $to_line p" ticks > $OUTPUT_DIR/$stimul.xml
		from_line=$(($to_line + 1)) 
		stimul_record_start=$(echo $stimul_start $wav_start | awk '{print $1-$2}')
		sox $WAV_FILE $OUTPUT_DIR/$stimul.wav trim $stimul_record_start $stimul_duration
	fi
done <$LOG_FILE

rm ticks



