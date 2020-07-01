#/bin/bash

read WORD

for i in $@; do
	if [ ! -e ${i} ]; then
		echo "File ${i} dont exist."
		continue
	fi
	echo "FILE ${i} has $(cat ${i}| grep "${WORD}"|wc -l) matches."
done
