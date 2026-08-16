#!/usr/bin/bash

CC="gcc"

FLAGS="-static -O3 \
	-ffast-math -fwhole-program"

MACROS="-D_sine_exe"
OUTPUT="sine"
SOURCES=$(ls *.c)

if ! [ -x "$(command -v $CC)" ]; then
	echo "cannot find compiler '$CC'."
	exit 1
fi

$CC $FLAGS $MACROS -o $OUTPUT $SOURCES
error=$?

if [ $error -ne 0 ]; then
	echo "compilation failed."

	exit 1
fi

echo "successfully built '$OUTPUT'."
