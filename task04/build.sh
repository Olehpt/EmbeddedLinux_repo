#!/bin/bash

if [ $# -ne 2 ]; then
	echo "Script uses 2 arguments - name of executable, name of .c file"
	exit 1
fi

EXEC_NAME=$1
SRC_NAME=$2

gcc -Wall -Wextra -o "$EXEC_NAME" "$SRC_NAME"

if [ $? -eq 0 ]; then
	echo "Build succesful"
	exit 0
else
	echo "Build failure"
	exit 1
fi


