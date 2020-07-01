#!/bin/bash

if [ $# -ne 3 ]; then
	echo "Wrong number of arguments."
	exit 1
fi

if [ $(cat "${1}"| wc -l) -ne $(cat "${1}"| egrep "^.*="|wc -l) ]; then
	echo "Error in file structure."
fi

if [ $(cat "${1}"| egrep "^${2}="|wc -l) -ne 1 ]; then
	echo "niz 1 must apears once."
	exit 2
fi

if [ $(cat "${1}"| egrep "^${3}="|wc -l) -eq 1 ]; then
	niz1=$(cat "${1}"|egrep "^${2}="|cut -d '=' -f 2| tr ' ' '\n')
	niz2=$(cat "${1}"|egrep "^${3}="|cut -d '=' -f 2| tr ' ' '\n')
	niz3="${niz2}"
	while read element; do
		if [ $(grep "${element}" <(echo ${niz1})| wc -l) -gt 0 -a ${element} != ' ' ]; then
			niz2=$(echo ${niz2}|tr -d "${element}")
		fi
	done < <(echo "${niz3}")
	niz2=$(echo "${niz2}"|tr '\n' ' ')
	echo "${niz2}"
	sed -i -e "s/^${3}=.*/${3}=${niz2}/" "${1}"
fi
