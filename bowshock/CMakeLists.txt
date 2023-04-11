cmake_minimum_required(VERSION 3.21)

option(BOW_DATA_DIRECTORY "Directory for storing run-time data (assets, shaders...)." "")

if("${BOW_DATA_DIRECTORY}" STREQUAL "")
	message(FATAL_ERROR "Data directory (BOW_DATA_DIRECTORY) not specified")
endif()

set(CMAKE_CXX_STANDARD 23)

add_executable(
	bowshock
	
	"source/bs/objTypStr.cxx"
	"source/bs/rnd.cxx"

	"source/init/bow/bow.cxx"
	"source/init/bow/chkParams.cxx"
	"source/init/bow/compShd.cxx"
	"source/init/bow/compShdProg.cxx"
	"source/init/bow/cred.cxx"
	"source/init/bow/getQuot.cxx"
	"source/init/bow/getSavPth.cxx"
	"source/init/bow/help.cxx"
	"source/init/bow/init.cxx"
	"source/init/bow/initGfx.cxx"
	"source/init/bow/initRnd.cxx"
	"source/init/bow/initSig.cxx"
	"source/init/bow/intro.cxx"
	"source/init/bow/loop.cxx"
	"source/init/bow/pollEvts.cxx"
	"source/init/bow/priQuot.cxx"
	"source/init/bow/quit.cxx"

	"source/lgc/grav.cxx"
	"source/lgc/mv.cxx"
	"source/lgc/shipMass.cxx"
	"source/lgc/sim.cxx"

	"source/run/abrt.cxx"
	"source/run/addObj.cxx"
	"source/run/freeObjs.cxx"
	"source/run/genSys.cxx"

	"source/sav/genDat.cxx"
	"source/sav/cont.cxx"
	"source/sav/decSav.cxx"
	"source/sav/encSav.cxx"
	"source/sav/newSav.cxx"
	"source/sav/sav.cxx"
)

add_dependencies(
	bowshock

	glad
)

target_include_directories(
	bowshock PRIVATE

	"include"
)

target_link_libraries(
	bowshock PRIVATE

	flux
	glad
	glfw
	m
	zap
)

target_compile_definitions(
	bowshock PRIVATE

	_FORTIFY_SOURCE=$<IF:$<STREQUAL:"${CMAKE_BUILD_TYPE}","Debug">,0x0,0x2>
	_POSIX_C_SOURCE=200112l
	GLFW_INCLUDE_NONE
	bow_datDir="${BOW_DATA_DIRECTORY}"
	bow_dbg=$<IF:$<STREQUAL:"${CMAKE_BUILD_TYPE}","Debug">,true,false>
)

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang|GNU")
	target_compile_options(
		bowshock PRIVATE

		$<IF:$<STREQUAL:"${CMAKE_BUILD_TYPE}","Debug">,-Og,-Ofast>
		-Wall
		-Wextra
		-Wmissing-prototypes
		-Wpedantic
		-fdiagnostics-color=always
		-g
	)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	target_compile_options(
		bowshock PRIVATE

		/O2
		/W4
		$<IF:$<STREQUAL:"${CMAKE_BUILD_TYPE}","Debug">,/Zo>
	)
endif()
