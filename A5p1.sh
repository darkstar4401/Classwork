#!/bin/bash
#print all cmd args line by line
arr=("$@")

for arg in "${arr[@]}"
do
	echo "$arg"
done

#print all cmd args in alphabetical order
echo "after sorting in alphabetical order"
#if only one arg
if [ $# -eq 1 ]; then
	echo $1
fi
#if two cmd args echo smallest to largest
if [ $# -eq 2 ]; then
	if [[ $1 < $2 ]]; then
		echo $1
		echo $2
	else
		echo $2
		echo $1
fi
#if there are 3 args
if [ $# -eq 3 ]; then
if [[ $1 > $2 ]];then
	if [[ $2 < $3 ]] && [[ $1 < $3 ]]; then
		echo $2
		echo $1
		echo $3
	elif [[ $2 > $3 ]] && [[ $1 > $3 ]]; then
		echo $3
		echo $1
		echo $2
	elif [[ $2 < $3 ]] && [[ $1 < $3 ]]; then
		echo $2
		echo $1
		echo $3
fi
if [[ $1 < $2 ]]
	if [[ $2 < $3 ]] && [[ $1 < $3 ]]; then
		echo $1
		echo $2
		echo $3
	elif [[ $2 > $3 ]] && [[ $1 > $3 ]]; then
		echo $1
		echo $3
		echo $2
	elif [[ $2 < $3 ]] && [[ $1 > $3 ]]; then
		echo $3
		echo $2
		echo $1
fi


