#!/bin/bash

# With any argument use gdb
PATH=../bin:$PATH
if [ -n "$1" ]
then
    if [ "$1" = "cgdb" ]
    then
        LD_LIBRARY_PATH=./lib cgdb ./bin/test
    else
        LD_LIBRARY_PATH=./lib gdb ./bin/test
    fi
else
	LD_LIBRARY_PATH=./lib ./bin/test
fi

