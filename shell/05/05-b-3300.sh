#!/bin/bash

if [ $# -ne 0 ]; then
	echo "Wrong arg. number"
	exit 1
fi
read -p "f1: " FILE1
read -p "f2: " FILE2
read -p "f3: " FILE3
sort <(cat ${FILE1}; cat ${FILE2}) > $FILE3
