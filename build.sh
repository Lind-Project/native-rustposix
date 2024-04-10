#!/bin/bash

export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
$CC $CFLAGS tests/lind_platform.c -o tests/lind_platform.o

for test in $(cat "$1"); do
    $CC $CFLAGS tests/$test.c -o tests/$test.o
    $CC $CFLAGS tests/$test.o tests/lind_platform.o $LDFLAGS -o tests/$test
done
