#!/usr/bin/bash

CC=$(command -v gcc)

LINKING_FLAGS="-static -flto \
	-nostartfiles -fno-builtin \
	-fno-stack-protector"

OPTIMIZATION_FLAGS="-O3 -ffast-math \
	-ftree-vectorize \
	-fomit-frame-pointer"

WARNING_FLAGS="-Wall -Wextra -Wno-switch-bool"

FLAGS="$RUNTIME_FLAGS $OPTIMIZATION_FLAGS \
	$WARNING_FLAGS"

MACROS="-D_sine_exe"
OUTPUT="sine"
SOURCES=$(ls *.c)

if [ "$(command -v $CC)" == "" ]; then
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
