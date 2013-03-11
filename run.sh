#!/bin/bash

# With any argument use gdb
if [ -n "$1" ]
then
	LD_LIBRARY_PATH=./lib gdb ./bin/example
else
	LD_LIBRARY_PATH=./lib ./bin/example
fi

