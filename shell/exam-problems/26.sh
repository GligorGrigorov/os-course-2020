[ $# -eq 2 ] || { echo "Usage..."; exit 1; }
[ -d ${2} ] || { echo "First arg. not dir."; exit 2; }
[ $(find ${2}|wc -l) -eq 1 ] || { echo "Dir. not empty."; exit 3; }
[ -f ${1} ] || { echo "File does not exist."; exit 4; }

f="${1}"
d="${2}"

lines=$(cat ${f}|wc -l)
pattern="^[a-zA-Z-]+[ ]+[a-zA-Z-]+.*:.*$"
matchingLines=$(cat ${f}|egrep "${pattern}"| wc -l)

[ ${lines} -eq ${matchingLines} ] || { echo "Error in file structure."; exit 5; }

names=$(mktemp)

cat ${f}|egrep -o "^[a-zA-Z-]+[ ]+[a-zA-Z-]+"|tr -s ' '|sort|uniq > ${names}
counter=1
while read firstName lastName; do
	echo "${firstName} ${lastName};${counter}" >> "${d}/dict.txt"
	while read line; do
		echo "${line}" >> "${d}/${counter}.txt"
	done < <(cat ${f}|egrep "^${firstName}[ ]+${lastName}")
	counter=$(expr ${counter} + 1)
done < ${names}



rm ${names}
