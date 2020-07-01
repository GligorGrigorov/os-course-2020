#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Wrong arg. num."
	exit 1
fi

find ${1} -type f|xargs md5sum | sort -k 1|rev| uniq -f 1 -D|rev


