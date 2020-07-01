#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Wrong argument number."
	exit 1
fi
FIRST=$1
EXPR=$(echo $FIRST| egrep -x "[[:alnum:]]+"| wc -l)

#echo "$EXPR"

if [ ${EXPR} -eq 1 ]; then
	echo "yes"
else
	echo "no"
fi
