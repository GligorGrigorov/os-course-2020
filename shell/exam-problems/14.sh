#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Wrong number of arguments."
	exit 1
fi
echo "deb 1"
if [ $(egrep -xc "^[+-]?[0-9]+$" <(echo $1)) -ne 1 ]; then
	echo "Not valid argument(number)"
	exit 2
fi

echo "deb 2"
USERS=$(mktemp)

ps -e -o user= | sort| uniq > ${USERS}

while read usr; do

	echo "debug 1";
	totalRSS=0
	while read currentRSS; do

		echo "debug 2";
		totalRSS=$(expr ${totalRSS} + ${currentRSS})
	done < <(ps -u ${usr} -o rss)

	echo "User ${usr} has ${totalRSS} rss."

done < <(cat ${USERS})

rm ${users}
