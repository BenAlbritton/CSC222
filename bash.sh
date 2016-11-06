#!/bin/bash
#filename="$1"
filename="./project2/fork.c"
count=$count
count=0
while read -r line
do
	count = $count +1
	#name="$line"
	#echo "Name read from file - $name"
done #< "$count"
