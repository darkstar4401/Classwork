#!/bin/bash
# loop through 1-4 
for i in {1..4}
do
	#loop through 1-7
	for j in {1..7}
	do
		((k = $i*$j))
		#print function on line
		echo "$i * $j = $k"
	done
done