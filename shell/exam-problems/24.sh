#!/bin/bash

[ $(id -u) -eq 0 ] || { echo "Not root."; exit 1; }

psOutput=$(mktemp)
ps aux| tail -n +2 > ${psOutput}

while read line; do
	usr=$(echo "${line}"|awk '{print $1}')
	id=$(id -u ${usr} 2> /dev/null)
	homeDir=$(cat /etc/passwd|cut -d: -f3,6| egrep "^${id}:"|cut -d: -f2)
	if [ ! -d ${homeDir} ]; then
		echo "${line}"| awk '{print $2}'
		continue
	fi
	if [ $(ls -ld ${homeDir}| awk '{print $2}') != ${usr} ]; then
		echo "${line}"| awk '{print}'
		continue
	fi	
	if [ $(ls -ld ${homeDir}|cut -c 3) -ne 'w' ]; then
		echo "${line}"| awk '{print}'
		continue
	fi	
done < <(cat ${psOutput}| egrep -v "^root")

rm ${psOutput}
