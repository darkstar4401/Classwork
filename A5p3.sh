#!/bin/bash
#function to do equation
function equation{
	#use numerical
	((k = $i*$k))
	#print function on line
	echo "$i * $j = $k"
}

#loop through 1-4 
for i in {1..4};
do
	#loop through 1-7
	for j in {1..7};
	do
		equation "$i" "$j"
	done
done