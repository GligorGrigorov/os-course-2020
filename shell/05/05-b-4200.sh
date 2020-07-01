#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Wrong argument number."
	exit 1
fi

TEST=$(find . -name $1| wc -l)

if [ $TEST -ne 1 ]; then
	echo "File do not exist."
	exit 2
fi

INPUT=$(cat $1 | sed -r 's/[^{}]//g'| sed -r 's/([{}])/\1\n/g')

COUNTER=0
MAXDEPTH=0
for i in $INPUT; do
	if [ $i = "{" ]; then
		COUNTER=$(($COUNTER+1))
		if [ $COUNTER -gt $MAXDEPTH ]; then
			MAXDEPTH=${COUNTER}
		fi
	else
		COUNTER=0
	fi
done

echo "MAXDEPTH= ${MAXDEPTH}"
