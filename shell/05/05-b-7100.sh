#!/bin/bash

if [ $# -ne 2 ]; then
	echo "Wrong ar. num."
	exit 1
fi

DIRNAME=${1}
NUM=${2}

find ${DIRNAME} -type f -size +${NUM} -printf "%p\n"
