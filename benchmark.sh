#!/usr/bin/bash

echo -e "SUBJECT\t======\t$1"
echo -e "OBJECT\t======\t$2"

echo -e \
"\n###################################\n"

if [ ls "tests/$1" >/dev/null 2>&1 ]; then
	echo "'$1' path not found."
	exit 1
fi

if [ ls "tests/$2" >/dev/null 2>&1 ]; then
	echo "'$2' path not found."
	exit 1
fi

FILETYPES="*.sn *py *.lua"

SUBJECT_SCRIPTS=$(ls "tests/$1" $FILE_TYPES)
OBJECT_SCRIPTS=$(ls "tests/$2" $FILE_TYPES)

SINE=$(which ./sine)
PYTHON="python3"
LUA="lua"

OLD_DIR=$(echo $PWD)

scripts=$SUBJECT_SCRIPTS
cd "tests/$1"

for script in $(echo $scripts | tr " " "\n")
do
	path=$script
	echo -e "======\t$script\t======"

	case $script in *.sn) \
time -p $SINE _run $path;; esac
	case $script in *.py) \
time -p $PYTHON $path;; esac
	case $script in *.lua) \
time -p $LUA $path;; esac
done

echo -e \
"\n###################################\n"

cd $OLD_DIR

scripts=$OBJECT_SCRIPTS
cd "tests/$2"

for script in $(echo $scripts | tr " " "\n")
do
	path=$script
	echo -e "======\t$script\t======"

	case $script in *.sn) \
time -p $SINE _run $path;; esac
	case $script in *.py) \
time -p $PYTHON $path;; esac
	case $script in *.lua) \
time -p $LUA $path;; esac
done

cd $OLD_DIR
