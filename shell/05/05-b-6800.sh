#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Wrong arg. num."
	exit 1
fi

find ${1} -type f -printf "%f %s\n"| egrep -v "^[\.]"

while read LINE; do
	echo "${LINE} $(find ${LINE} |wc -l)"
done< <(find ${1} -type d) 
