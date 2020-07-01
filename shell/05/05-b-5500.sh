#!/bin/bash

FILENAME=$1

tableRow(){
	for i in ${@}; do
		echo <>
	done
}

tableHeader(){
	echo "<th>${1}</th>"
}

if [ $# -ne 1 ]; then
	echo "Wrong arg. num."
fi

output="<table>\n"

th="\t\t<th>"
the="</th>"

header="<>"

row="\t<tr>\n\t</tr>\n"

output=${output}"</table>\n"

