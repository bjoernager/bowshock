#!/bin/sh

installBinary() {
	buildDirectory="${1}"
	binaryDirectory="${2}"

	mkdir -pvm755 "${binaryDirectory}"

	install -vm755 "${buildDirectory}/bowshock/bowshock" "${binaryDirectory}"/bowshock
}

installData() {
	sourceDirectory="${1}"
	dataDirectory="${2}"

	mkdir -pvm755 "${dataDirectory}/shaders"

	install -vm644 "${sourceDirectory}/CHANGELOG.md" "${dataDirectory}"
	install -vm644 "${sourceDirectory}/CREDITS.txt" "${dataDirectory}"
	install -vm644 "${sourceDirectory}/bowshock/shader/"*".glsl" "${dataDirectory}/shaders"
}

echo installing "${1}"

if [ "${1}" == "data" ]
then
	if [ -z "${2}" ]
	then
		echo failure: data directory is not set
		exit 2
	fi

	sourceDirectory="${PWD}"
	dataDirectory="${2}"

	installData "${sourceDirectory}" "${dataDirectory}"

	echo done

	exit 0
elif [ "${1}" == "all" ]
then
	if [ -z "${2}" ]
	then
		echo failure: build directory is not set
		exit 3
	fi

	if [ -z "${3}" ]
	then
		echo failure: binary directory is not set
		exit 2
	fi

	if [ -z "${4}" ]
	then
		echo failure: data directory is not set
		exit 1
	fi

	sourceDirectory="${PWD}"
	buildDirectory="${2}"
	binaryDirectory="${3}"
	dataDirectory="${4}"

	installBinary "${buildDirectory}" "${binaryDirectory}"
	installData "${sourceDirectory}" "${dataDirectory}"
fi

echo done
