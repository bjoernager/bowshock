cmake_minimum_required(VERSION 3.21)

option(BOW_DATA_DIRECTORY "Directory for storing run-time data (assets, shaders...)." "")

if("${BOW_DATA_DIRECTORY}" STREQUAL "")
	message(FATAL_ERROR "Data directory (BOW_DATA_DIRECTORY) not specified")
endif()

set(CMAKE_CXX_STANDARD 20)

add_executable(
	bowshock
	
	"source/bs/objtypstr.cxx"
	"source/bs/rnd.cxx"

	"source/ini/bow/chkpar.cxx"
	"source/ini/bow/cmpshdprg.cxx"
	"source/ini/bow/exi.cxx"
	"source/ini/bow/getquo.cxx"
	"source/ini/bow/getsavpth.cxx"
	"source/ini/bow/hlp.cxx"
	"source/ini/bow/ini.cxx"
	"source/ini/bow/inigfx.cxx"
	"source/ini/bow/inirnd.cxx"
	"source/ini/bow/inisig.cxx"
	"source/ini/bow/lop.cxx"
	"source/ini/bow/polevt.cxx"
	"source/ini/bow/pricrd.cxx"
	"source/ini/bow/priquo.cxx"
	"source/ini/bow/srtseq.cxx"

	"source/lgc/grv.cxx"
	"source/lgc/mov.cxx"
	"source/lgc/shpmas.cxx"
	"source/lgc/sim.cxx"

	"source/run/abr.cxx"
	"source/run/addobj.cxx"
	"source/run/remobj.cxx"
	"source/run/gensys.cxx"

	"source/sav/gendat.cxx"
	"source/sav/cnt.cxx"
	"source/sav/decsav.cxx"
	"source/sav/encsav.cxx"
	"source/sav/newsav.cxx"
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

	glad
	glfw
	ly
	m
	zp
)

target_compile_definitions(
	bowshock PRIVATE

	_FORTIFY_SOURCE=$<IF:$<STREQUAL:"${CMAKE_BUILD_TYPE}","Debug">,0x0,0x2>
	_POSIX_C_SOURCE=200112l
	GLFW_INCLUDE_NONE
	bow_datdir="${BOW_DATA_DIRECTORY}"
	bow_dbg=$<IF:$<STREQUAL:"${CMAKE_BUILD_TYPE}","Debug">,true,false>
)

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang|GNU")
	target_compile_options(
		bowshock PRIVATE

		$<IF:$<STREQUAL:"${CMAKE_BUILD_TYPE}","Debug">,-Og,-Ofast>
		-Wall
		-Wdouble-promotion
		-Wextra
		-Wfloat-equal
		-Wformat=2
		-Winvalid-utf8
		-Wmissing-declarations
		-Wmissing-include-dirs
		-Wnull-dereference
		-Wpedantic
		-Wpointer-arith
		-Wstrict-overflow=5
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
