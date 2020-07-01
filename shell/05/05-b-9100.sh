#!/bin/bash

if [ $# -ne 2 ]; then
	echo "Wrong arg num"
	exit 1
fi

SOURCE=${1}
DEST=${2}

while read line; do
	mkdir "${DEST}/${line}"
	find ${SOURCE} -type f -printf "%p\n"|egrep "${line}$"|xargs cp {} "${DEST}/${line}" \;
done < <(find ${SOURCE} -type f -printf "%f\n"|egrep -o "[.][[:alnum:]]+$"|sort|uniq|cut -c 2-)
