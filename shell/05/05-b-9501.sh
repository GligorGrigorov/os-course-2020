#!/bin/bash

if [ $# -ne 1 ];then
	echo "Wrong arg. num."
	exit 1
fi
if [ $1 = "-r" ]; then
	counter=0
fi
if [ $1 = "-g" ]; then
        counter=1
fi
if [ $1 = "-b" ]; then
        counter=2
fi
if [ $1 = "-x" ]; then
	while read LINE; do
		echo $LINE
	done
	exit 0
fi

while read LINE; do
	if [ $((counter % 3)) -eq 0 ]; then
		echo -e "\033[0;31m $LINE"
	fi
	if [ $((counter % 3)) -eq 1 ]; then
		echo -e "\033[0;32m $LINE"
	fi
	if [ $((counter % 3)) -eq 2 ]; then
                echo -e "\033[0;34m $LINE"
        fi
	counter=$(($counter + 1))
done
