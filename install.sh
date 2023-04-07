#!/bin/sh

installBinary() {
	builddir="${1}"
	bindir="${2}"

	mkdir -pvm755 "${bindir}"
	
	install -vm755 "${builddir}/bowshock/bowshock" "${bindir}"/bowshock
}

installData() {
	srcdir="${1}"
	datdir="${2}"

	mkdir -pvm755 "${datdir}/shaders"
	
	install -vm644 "${srcdir}/CHANGELOG.txt" "${datdir}"
	install -vm644 "${srcdir}/CREDITS.txt" "${datdir}"
	install -vm644 "${srcdir}/bowshock/shader/"*".glsl" "${datdir}/shaders"
}

if [ "${1}" == "data" ]
then
	echo installing data...

	if [ -z "${2}" ]
	then
		echo failure: data directory is not set
		exit 2
	fi

	srcdir="${PWD}"
	datdir="${2}"

	installData "${srcdir}" "${datdir}"

	echo done

	exit 0
fi

echo installing all...

if [ -z "${1}" ]
then
	echo failure: build directory is not set
	exit 3
fi

if [ -z "${2}" ]
then
	echo failure: binary directory is not set
	exit 2
fi

if [ -z "${3}" ]
then
	echo failure: data directory is not set
	exit 1
fi

srcdir="${PWD}"
builddir="${1}"
bindir="${2}"
datdir="${3}"

installBinary "${builddir}" "${bindir}"
installData "${srcdir}" "${datdir}"

echo done
