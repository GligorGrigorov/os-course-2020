#!/bin/bash

[ $# -eq 2 ] || { echo "Usage...."; exit 1; }

[ -d ${1} ] || { echo "First argument is not a directory."; exit 2; }

files=$(mktemp)
find ${1} -maxdepth 1 -type f -printf "%f\n"|egrep "vmlinuz-([[:digit:]]+.){2}[[:digit:]]+-${2}" > ${files}

cat ${files}|egrep "vmlinuz-$(cat ${files}| cut -d '-' -f 2| sort -t '.' -nr| head -n 1)-${2}"
