#!/bin/bash

RAND=$(($RANDOM % 100))

while read LINE; do
	if [ $LINE -eq $RAND ]; then
		echo "YES"
		exit 0
	fi
	if [ $LINE -lt $RAND ]; then
		echo "GREATER"
	else
		echo "LOWER"
	fi

done
