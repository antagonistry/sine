#!/usr/bin/bash

CC="gcc"
FLAGS="-O3 -ffast-math -fwhole-program"
MACROS="-D_sine_exe"
OUTPUT="sine"
SOURCES=$(ls *.c)

if [ command -v $CC >/dev/null 2>&1 ]; then
	echo "$CC is not installed."
fi

$CC $FLAGS $MACROS -o $OUTPUT $SOURCES
