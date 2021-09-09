#!/bin/bash

code="$PWD"
opts=-g
cd build > /dev/null
g++ $opts $code/src/main.c -o arena_test
cd $code > /dev/null
