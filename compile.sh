#!/bin/bash
err="❌" 
ok="✅"


function compile {
	glue=""
	for i in "$@"; do
		if [ "$i" != "$1" ]; then
			glue="$glue $i"
		fi
	done
	gcc -Wall -Wextra -g -fsanitize=address  -fcompare-debug-second -I . ./cpy.c $programName
	if [ "$?" != "0" ]; then
		echo -e "$err Program not compiled"
		exit 1
	else
		echo "$ok Program compiled"
	fi
}


programName=$1
if [ "$programName" = "" ]; then
	echo "$err Program name not provided 😅"
	exit
fi


compile
if [ "$?" = "0" ]; then
	echo "$ok Executing binary"
	./a.out
fi
