#!/bin/bash

if [ $# -ne 3 ]; then
	echo "Wrong arg. num"
	exit 4
fi

num=${1}
leftSide=${2}
rightSide=${3}

#echo "${num}\n${leftSide}\n${rightSide}"|egrep -x "[0-9]+"| wc -l

if [ $(echo "${num}\n${leftSide}\n${rightSide}"|egrep "[.]"| wc -l) -ne 0 ]; then
	exit 3
fi

if [ $leftSide -gt $rightSide ]; then
	exit 2
fi

if [ ${num} -ge ${leftSide} ] && [ ${num} -le ${rightSide} ]; then
	exit 0
fi

exit 1

