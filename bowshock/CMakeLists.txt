cmake_minimum_required(VERSION 3.21)

option(BOW_DATA_DIRECTORY "Directory for storing run-time data (assets, shaders...)." "")

if("${BOW_DATA_DIRECTORY}" STREQUAL "")
	message(FATAL_ERROR "Data directory (BOW_DATA_DIRECTORY) not specified")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(
	bowshock

	"source/application/bow/compile_shader_program.cxx"
	"source/application/bow/configure.cxx"
	"source/application/bow/destructor.cxx"
	"source/application/bow/get_quote.cxx"
	"source/application/bow/initialise_graphics.cxx"
	"source/application/bow/initialise_random.cxx"
	"source/application/bow/initialise_signal.cxx"
	"source/application/bow/loop.cxx"
	"source/application/bow/poll_events.cxx"
	"source/application/bow/print_credits.cxx"
	"source/application/bow/print_help.cxx"
	"source/application/bow/print_quote.cxx"
	"source/application/bow/run.cxx"
	"source/application/bow/start_sequence.cxx"

	"source/base/home_directory.cxx"
	"source/base/object_type_string.cxx"
	"source/base/random.cxx"
	"source/base/save_path.cxx"

	"source/logic/gravitate.cxx"
	"source/logic/move.cxx"
	"source/logic/ship_mass.cxx"
	"source/logic/simulate.cxx"

	"source/runtime/add_object.cxx"
	"source/runtime/generate_system.cxx"
	"source/runtime/delete_objects.cxx"

	"source/save/continue_save.cxx"
	"source/save/decode_save.cxx"
	"source/save/encode_save.cxx"
	"source/save/new_save.cxx"
	"source/save/save.cxx"
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

	fmt
	glad
	glfw
	m
)

target_compile_definitions(
	bowshock PRIVATE

	_FORTIFY_SOURCE=$<IF:$<STREQUAL:"${CMAKE_BUILD_TYPE}","Debug">,0x0,0x2>
	_POSIX_C_SOURCE=200112l
	GLFW_INCLUDE_NONE
	bow_dataDirectory="${BOW_DATA_DIRECTORY}"
	bow_debug=$<IF:$<STREQUAL:"${CMAKE_BUILD_TYPE}","Debug">,true,false>
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
