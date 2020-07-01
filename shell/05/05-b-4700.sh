#!/bin/bash

if [ $# -ne 1 ] && [ $# -ne 2 ]; then
	echo "Wrong arg. num."
	exit 1
fi

input=${1}
delim=${2}

var=$(echo "${input}"|rev| sed -e 's/\(.\)/\1\n/g')
counter=0
output=""
for i in $var ; do
	if [ $(($counter % 3)) -eq 0 ] && [ $counter -ne 0 ]; then
		output="$output$delim"
	fi
	counter=$(($counter+1))
	output="$output"$i
done

echo "$(echo $output|rev)"

