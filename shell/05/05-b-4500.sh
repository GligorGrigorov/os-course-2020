#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Wrong arg number."
	exit 1
fi

if [ $(cat /etc/passwd| egrep "^${1}"|wc -l) -ne 1 ]; then
	echo "No such user."
	exit 2
fi

while [ $(who|grep "${1}"| wc -l) -lt 1 ]; do
	sleep 1
done

echo "${1} is loged in."
