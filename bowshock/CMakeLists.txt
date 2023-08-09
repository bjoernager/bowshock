cmake_minimum_required(VERSION 3.21)

option(BOW_DATA_DIRECTORY "Directory for storing run-time data (assets, shaders...)." "")

if(NOT DEFINED BOW_DATA_DIRECTORY)
	message(FATAL_ERROR "Data directory (BOW_DATA_DIRECTORY) not specified")
endif()

find_package(
	glfw3 REQUIRED
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(
	bowshock

	"source/main.cxx"

	"source/application/Application/constructor.cxx"
	"source/application/Application/destructor.cxx"
	"source/application/Application/get_quote.cxx"
	"source/application/Application/initialise_signal.cxx"
	"source/application/Application/parse_parameters.cxx"
	"source/application/Application/print_credits.cxx"
	"source/application/Application/print_help.cxx"
	"source/application/Application/run.cxx"

	"source/client/Client/constructor.cxx"
	"source/client/Client/destructor.cxx"
	"source/client/Client/loop.cxx"
	"source/client/Client/poll_events.cxx"
	"source/client/Client/run.cxx"
	"source/client/Client/save_path.cxx"
	"source/client/Client/start_sequence.cxx"
	"source/client/PlayerData/constructor.cxx"
	"source/client/PlayerData/decode_save.cxx"
	"source/client/PlayerData/encode_save.cxx"
	"source/client/PlayerData/load.cxx"
	"source/client/PlayerData/read_file.cxx"
	"source/client/PlayerData/save.cxx"
	"source/client/PlayerData/write_file.cxx"
	"source/client/Renderer/constructor.cxx"
	"source/client/Renderer/destructor.cxx"
	"source/client/Renderer/render.cxx"
	"source/client/ShaderProgram/compile_shader.cxx"
	"source/client/ShaderProgram/constructor.cxx"
	"source/client/ShaderProgram/destructor.cxx"

	"source/base/base_directory.cxx"
	"source/base/terminate.cxx"

	"source/logic/Canister/constructor.cxx"
	"source/logic/Canister/object_type_string.cxx"
	"source/logic/Object/object_type_string.cxx"
	"source/logic/Ship/constructor.cxx"
	"source/logic/Ship/net_mass.cxx"
	"source/logic/Ship/object_type_string.cxx"
	"source/logic/Star/constructor.cxx"
	"source/logic/Star/object_type_string.cxx"
	"source/logic/Station/constructor.cxx"
	"source/logic/Station/object_type_string.cxx"
	"source/logic/ware_mass.cxx"
	"source/logic/World/constructor.cxx"
	"source/logic/World/object_type_string.cxx"

	"source/server/ObjectIterator/constructor.cxx"
	"source/server/ObjectIterator/operator_equality.cxx"
	"source/server/ObjectIterator/operator_increment.cxx"
	"source/server/ObjectRoot/add.cxx"
	"source/server/ObjectRoot/begin.cxx"
	"source/server/ObjectRoot/constructor.cxx"
	"source/server/ObjectRoot/destructor.cxx"
	"source/server/ObjectRoot/end.cxx"
	"source/server/Server/destructor.cxx"
	"source/server/Server/start.cxx"
	"source/server/ServerInstance/constructor.cxx"
	"source/server/ServerInstance/generate_system.cxx"
	"source/server/ServerInstance/gravitate.cxx"
	"source/server/ServerInstance/loop.cxx"
	"source/server/ServerInstance/move.cxx"
	"source/server/ServerInstance/run.cxx"
	"source/server/ServerInstance/simulate.cxx"
)

add_dependencies(
	bowshock

	glad
	glfw
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

	GLFW_INCLUDE_NONE
	bow_DATA_DIRECTORY="${BOW_DATA_DIRECTORY}"
	bow_DEBUG=$<IF:$<STREQUAL:"${CMAKE_BUILD_TYPE}","Debug">,true,false>
)

if(UNIX)
	target_compile_definitions(
		bowshock PRIVATE

		_FORTIFY_SOURCE=$<IF:$<STREQUAL:"${CMAKE_BUILD_TYPE}","Debug">,0x0,0x2>
		_POSIX_C_SOURCE=200112l
	)
endif()

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang|GNU")
	target_compile_options(
		bowshock PRIVATE

		$<IF:$<STREQUAL:"${CMAKE_BUILD_TYPE}","Debug">,-Og,-Ofast>
		-Wall
		-Wdouble-promotion
		-Wextra
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
