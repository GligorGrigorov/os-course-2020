#!/bin/bash

N=10

[ $# -gt 0 ] || { echo "Wrong ars."; exit 3; }

if [ ${1} = "-n" -a $# -gt 2 ]; then
	N=${2}	
	shift 2
else
	if [ $# -lt 1 ]; then
		echo "Usage..."
		exit 1
	fi
fi

output=$(mktemp)
while [ $# -ne 0 ]; do
	if [ ! -f ${1} ]; then
		echo "${1} not file"
		exit 2
	fi 
	while read date hours data; do
		echo "${date} ${hours} $(echo "${1}"| cut -d '.' -f 1) ${data}" >>${output}
	done < <(cat ${1}| tail -n ${N})
	shift 1
done

cat ${output}|sort -n

rm ${output}

