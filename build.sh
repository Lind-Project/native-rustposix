#!/bin/bash

RUSTPOSIX_PATH="${RUSTPOSIX_PATH:-/home/lind/lind_project/src/safeposix-rust/target/release}"
if [ ! -f $RUSTPOSIX_PATH/librustposix.so ]; then
    echo "File not found: $RUSTPOSIX_PATH/librustposix.so"
    exit 127
fi

echo "Copying librustposix.so"
cp $RUSTPOSIX_PATH/librustposix.so .

export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
$CC $CFLAGS tests/lind_platform.c -o tests/lind_platform.o

for test in $(cat "$1"); do
    $CC $CFLAGS tests/$test.c -o tests/$test.o
    $CC $CFLAGS tests/$test.o tests/lind_platform.o $LDFLAGS -o tests/$test
done
