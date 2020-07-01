#!/bin/bash

if [ $# -ne 2 ]; then
	echo "Wrong arg. num"
	exit 1
fi

DIR=${1}
NUM=${2}
if [ ! -d ${DIR} ]; then
	echo "Wrong dir name."
	exit 2
fi

if [ ${NUM} -le 0 ]; then
	echo "Size must be > 0"
	exit 3
fi

SUMSIZE=0

while read LINE; do
	SUMSIZE=$(($SUMSIZE + ${LINE}))	
done < <(find ${DIR} -type f -size "+${NUM}" -printf "%s\n")
echo "SIZE: ${SUMSIZE}"
