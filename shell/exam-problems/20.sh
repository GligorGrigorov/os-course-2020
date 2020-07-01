#!/bin/bash

if [ $# -ne 3 ]; then
	echo "Wrong num..."
	exit 1
fi
SRC="$(dirname "${1}"/"$(basename "${1}")")"
DST="$(dirname "${2}"/"$(basename "${2}")")"
ABC="${3}"

[ -d "${SRC}" ] || { echo "SRC  not dir."; exit 2;}
[ -d "${DST}" ] || { echo "DST  not dir."; exit 3;}
[ $(find ${DST} -type f|wc -l) -eq 0 ] || { echo "DST not empty"; exit 4;}
#[ $(id -u) -eq 0 ] || { echo "Not root user."; exit 5;}

filesToMove=$(mktemp)
find ${SRC} -type f -name "*${ABC}*" > ${filesToMove}

cat ${filesToMove}

for i in $(find "${SRC}" -type f -name "*${ABC}*"); do
	DSTFILE=$(echo "${i}"| sed -e "s|${SRC}|${DST}|")
	mkdir -p $(dirname $DSTFILE)
	mv ${i} ${DSTFILE}	
done
