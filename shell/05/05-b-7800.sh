#!/bin/bash

if [ $# -ne 0 ]; then
	echo "Wrong arg. num"
	exit 1
fi
NUMBER=0
while read -d ":" LINE; do
	NUMBER=$(($NUMBER + $(find $LINE -executable|wc -l)))	
done < <(echo $PATH)
echo $NUMBER
