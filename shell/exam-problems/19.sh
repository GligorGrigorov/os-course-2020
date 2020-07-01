#!/bin/bash

if [ $# -lt 1 -o $# -gt 2 ]; then
	echo "Wrong number of arguments."
	exit 1
fi

if [ $# -eq 2 ]; then
	find ${1} -type f -printf "%n %f\n"| awk -v h="${2}" '{if ( $1 == h ) printf "%s %s\n",$1,$2}'
fi

if [ $# -eq 1 ]; then
	find ${1} -type l ! -exec test -e {} \; -printf "%f\n"
fi
