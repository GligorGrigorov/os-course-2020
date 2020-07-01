#!/bin/bash
file=$(mktemp)
find / -type f -printf "%T@ %p\n" 2> /dev/null|sort -n |tail -n 1| cut -d ' ' -f2 > ${file}

directories=$(mktemp)
cat /etc/passwd|cut -d ':' -f 6 > ${directories}

homeDirs=$(mktemp)
while read line; do
	egrep -o "^$line" ${file} >> ${homeDirs}
done < ${directories}

while read line; do
	if [ ${line} != "/" ]; then
		egrep "^([^:]*:){5}${line}" /etc/passwd| cut -d: -f 1
	fi
done < ${homeDirs}
