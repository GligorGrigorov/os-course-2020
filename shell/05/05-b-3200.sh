#!/bin/bash

if [ $# -ne 0 ]; then
	echo "Arguments not supported."
	exit 1
fi

read -p "Enter directory: " DIRNAME

echo "Files number: "
wc -l < <(find $DIRNAME -type f)

echo "Dir number: "
wc -l < <(find $DIRNAME -type d)

