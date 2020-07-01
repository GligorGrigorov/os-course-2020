#!/bin/bash

abs () {
	[ ${1} -lt 0 ] || { echo "$1"; return; }
	echo $(expr 0 - ${1})
	return
}
sum () {
	
}

[ $# -eq 0 ] || { echo "Usage..."; exit 1; }

input=$(mktemp)
input2=$(mktemp)
while read line; do
	echo "${line}" >> ${input}
done
cat ${input}| egrep "^-?[0-9]+$"| sort -n > ${input2}
first=$(cat ${input2}| head -n 1)
last=$(cat ${input2}| tail -n 1)
if [ $(abs ${last}) -gt $(abs ${first}) ]; then
	echo "${last}"
	rm ${input}
	exit 1
fi

sums=$(mktemp)
if [ $(abs ${last}) -lt $(abs ${first}) ]; then
	echo "${first}"
	rm ${input}
	exit 1
fi
echo "${first}"
echo "${last}"
echo "========================="

while read line; do
	absLine=$(abs ${line})
	echo "$(sum ${absLine}) ${line}" >> ${sums}
done < ${input2}

cat ${sums}

rm ${sums}
rm ${input}
exit 1
