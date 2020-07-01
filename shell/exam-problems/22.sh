#!/bin/bash

if [ $# -lt 1 -o $# -gt 2 ]; then
	echo "Usage:..."
	exit 1
fi

links=$(mktemp)
if [ $# -eq 1 ]; then
	count=0
	find ${1} -type l 2> /dev/null > ${links}
	for i in $(cat ${links}); do
		if [ -e ${i} ]; then
			echo "$(basename ${i}) -> $(readlink ${i})"
		else
			count=$(expr ${count} + 1)
		fi
	done 	
	echo "Broken symlinks: ${count}"	
fi
