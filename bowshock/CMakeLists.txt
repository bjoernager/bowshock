cmake_minimum_required(VERSION 3.21)

option(BOW_DATA_DIRECTORY "" "")
option(BOW_C2X_COMPATIBILITY "Predefined C2x macros for older compilers." FALSE)

if("${BOW_DATA_DIRECTORY}" STREQUAL "")
	message(FATAL_ERROR "Data directory (BOW_DATA_DIRECTORY) not specified")
endif()

set(CMAKE_C_STANDARD 23)

add_executable(
	bowshock
	
	"source/bs/objTypStr.c"
	"source/bs/rnd.c"

	"source/init/chkParams.c"
	"source/init/compShd.c"
	"source/init/compShdProg.c"
	"source/init/cred.c"
	"source/init/getQuot.c"
	"source/init/getSavPth.c"
	"source/init/help.c"
	"source/init/init.c"
	"source/init/initGfx.c"
	"source/init/initRnd.c"
	"source/init/initSig.c"
	"source/init/priQuot.c"

	"source/lgc/grav.c"
	"source/lgc/mv.c"
	"source/lgc/shipMass.c"
	"source/lgc/sim.c"

	"source/run/abrt.c"
	"source/run/addObj.c"
	"source/run/freeObjs.c"
	"source/run/genSys.c"
	"source/run/intro.c"
	"source/run/loop.c"
	"source/run/pollEvts.c"
	"source/run/quit.c"

	"source/sav/genDat.c"
	"source/sav/cont.c"
	"source/sav/decSav.c"
	"source/sav/encSav.c"
	"source/sav/new.c"
	"source/sav/sav.c"
)

add_dependencies(
	bowshock

	glad
)

target_enable_warnings(bowshock)

target_enable_optimisations(bowshock)

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

	_POSIX_C_SOURCE=200112l
	GLFW_INCLUDE_NONE
	bow_datDir="/home/delta/Repositories/bowshock/datdir"
)

if(${BOW_C2X_COMPATIBILITY})
	target_compile_definitions(
		bowshock PRIVATE

		bow_c2xCompat
	)
endif()

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	target_compile_definitions(
		bowshock PRIVATE

		bow_dbg
	)
endif()

if("${CMAKE_C_COMPILER_ID}" MATCHES "Clang|GNU")
	target_compile_options(
		bowshock PRIVATE

		-Wmissing-prototypes
		-Wpedantic
		-fdiagnostics-color=always
		-g
	)
endif()

if("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
	target_compile_options(
		bowshock PRIVATE

		-Wno-fixed-enum-extension
		-Wno-gnu-folding-constant
		-Wno-gnu-empty-initializer
		-Wno-gnu-zero-variadic-macro-arguments
	) 
endif()
