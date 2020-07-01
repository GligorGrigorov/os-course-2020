#!/bin/bash

[ $# -eq 2 ] || { echo "Usage..."; exit 1; }
[ -f ${1} ] || { echo "Some of ags. are not files."; exit 2; }
[ ! -e ${2} ] || { echo "File ${2} exists."; exit 8; }
lines=$(cat ${1}|wc -l)
matchingLines=$(cat ${1}|egrep "^[ ]*[0-9]+[ ]*(,[^,]*)*"| wc -l)
comaNum=$(cat ${1}| sed -e "s/[^,]//g"|sort|uniq -c|awk '{print $1}' | head -n 1)

[ ${lines} -eq ${matchingLines} -a ${lines} -eq ${comaNum} ] || { echo "Error in file structure."; exit 3;}

uniqIDs=$(cat a.csv| awk -F ',' '{print $1}'|awk '{print $1}'|sort| uniq|wc -l)

[ ${uniqIDs} -eq ${lines} ] || { echo "IDs not uniq."; exit 1;}

newFile=$(mktemp)

while read line; do
	cat a.csv|egrep "^[ ]*[0-9]+[ ]*,${line}"|sort -n|head -n 1 >> ${newFile}
done < <(cat a.csv | cut -d, -f 2-|sort|uniq -c| awk '{printf("%s %s\n", $1, $2)}'| egrep -v "^1"|cut -d ' ' -f 2)
cat ${newFile}
echo "------------------"
f=$(mktemp)
cat a.csv | cut -d, -f 2-|sort|uniq -c| awk '{printf("%s %s\n" ,$1, $2)}'|egrep "^1"|cut -d ' ' -f 2 > ${f}

while read line; do
	cat ${1}|egrep "^[ ]*[0-9]+[ ]*,${line}" >> ${2}
done < ${f}

cat ${newFile} > ${1}
rm ${f}
rm ${newFile}
