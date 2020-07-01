#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Wrong number of args."
	exit 1
fi
uName="${1}"
if [ $(cat /etc/passwd| egrep "^${uName}:"|wc -l) -lt 1 ]; then
	echo "No such user."
	exit 2
fi
uProcNum=$(ps -e -o user|tail -n+2|grep "${uName}"|wc -l)
while read user1; do
	if [ $(ps -e -o user|tail -n+2|grep "${user1}"|wc -l) -gt ${uProcNum} ]; then
		echo "${user1}"
	fi
done < <(ps -e -o user|tail -n+2|sort| uniq)


avg=$(ps -e -o time| tail -n+2| awk -F ':' 'BEGIN {t = 0; c = 0}; {t = t + $1 * 3600 + $2 * 60 + $3; c = c + 1}; END {print(t/c)}') 

echo "AVG: ${avg}"


