#!/bin/bash

if [ $# -ne 0 ]; then
	echo "Arguments not supported."
	exit 1
fi

read -p "Enter file: " file
read -p "Enter word: " word

TEST=$(find . -name ${file}|wc -l)

if [ $TEST -eq 0 ]; then
	echo "File do not exist."
	exit 2
fi

grep -q "${word}" <(cat $file)

echo $?

