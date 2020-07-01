#!/bin/bash

if [ $# -ne 2 ]; then 
	echo "Wrong arg. number."
	exit 1
fi

file=${1}
dir=${2}

find ${dir} -type f 2> /dev/null |xargs md5sum {} 2> /dev/null| grep "$(md5sum ${file} | cut -d " " -f 1)"|rev| cut -d / -f 1| rev


