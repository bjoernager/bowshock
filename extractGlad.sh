#!/bin/sh

echo extracting GLAD...

if ! [ -z "${1}" ]
then
	archive="${1}"
else
	archive="glad.zip"
fi

if ! [ -e "${archive}" ]
then
	echo "failure: unable to access file \"${archive}\""
	exit 1
fi

unzip -od"glad" "${archive}"
cp -v "glad.CMakeLists.txt" "glad/CMakeLists.txt"

echo success
