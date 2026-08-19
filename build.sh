#!/usr/bin/bash

CC="gcc"

LINKING_FLAGS="-static -flto \
	-fno-stack-protector"

OPTIMIZATION_FLAGS="-Ofast -ftree-vectorize \
	-fsimd-cost-model=unlimited"

WARNING_FLAGS="-Wall -Wextra"

FLAGS="$RUNTIME_FLAGS $OPTIMIZATION_FLAGS \
	$WARNING_FLAGS"

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
