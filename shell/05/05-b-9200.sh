#!/bin/bash

if [ $# -lt 1 ]; then
	echo "Wrong arg. num."
	exit 1
fi

if [ ${1} = "-r" ]; then
	if [ $# -lt 2 ]; then
		echo "Wrong Arg. num."
		exit 2
	fi
	touch "${logFile}"
	shift 1
	while [ $# -ne 0 ]; do
		echo -n $(date) >> "${logFile}"
        	rm -rdv ${1} &>> "${logFile}"
        	shift 1
	done
	exit 0
fi
touch "${logFile}"
while [ $# -ne 0 ]; do
	echo -n $(date) >> "${logFile}"
	rm -dv ${1} &>> "${logFile}"
	shift 1;
done
