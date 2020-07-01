#!/bin/bash
echo "# os-course-2020" > README.md
echo "Materials from Operating Systems course at FMI-SU" >> README.md
links=$(mktemp)
find . -type d| grep -v "git"|cut -c 2-|sed -e "s|\(.*\)|https://github.com/GligorGrigorov/os-course-2020/tree/master\1|"| tail -n+2 > ${links}
while read link; do
	while read num; do
		while [ ${num} -ne 1 ]; do
			echo -n "	" >> README.md
			num=$(expr $num - 1)
		done
		echo "- [$(echo -n ${link}| rev| cut -d '/' -f 1| rev)](${link})" >> README.md
	done < <(echo "${link}"|sed -e 's|[^/]||g'|cut -c 8-|wc -m)
done < ${links}
