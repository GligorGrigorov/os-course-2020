#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Wrong arg.num"
	exit 1
fi

if [ -n "${1}" ]; then
    ps -u "${1}" -o pid,rss,vsz | tail -n +2 |  while read PID RSS VSZ; do
        SCALE=$(echo "scale=2; ${RSS}/${VSZ}" | bc)
        echo "process ${PID} takes up: ${SCALE}% of its virtual memory"
    done | tr . , | sort -t ':' -k2rn | tr , .
fi

