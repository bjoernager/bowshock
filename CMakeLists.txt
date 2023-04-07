cmake_minimum_required(VERSION 3.21)

project(
	bowshock

	VERSION 0.10.0
	HOMEPAGE_URL "https://mandelbrot.dk/bowshock"
	LANGUAGES C
)

function(target_enable_warnings TARGET)
	if("${CMAKE_C_COMPILER_ID}" MATCHES "Clang|GNU")
		target_compile_options(
			${TARGET} PRIVATE

			-Wall
			-Wextra
		)
	elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
		target_compile_options(
			${TARGET} PRIVATE

			/W4
		)
	endif()
endfunction()

function(target_enable_optimisations TARGET)
	if("${CMAKE_C_COMPILER_ID}" MATCHES "Clang|GNU")
		if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
			target_compile_options(
				${TARGET} PRIVATE

				-Og
			)
		else()
			target_compile_options(
				${TARGET} PRIVATE

				-Ofast
			)
		endif()
	elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
		target_compile_options(
			${TARGET} PRIVATE

			/O2
		)

		if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
			target_compile_options(
				${TARGET} PRIVATE

				/Zo
			)
		endif()
	endif()
endfunction()

if("${CMAKE_C_COMPILER_ID}" MATCHES "Clang|GNU")
	add_compile_options(
		-fdiagnostics-color=always
	)
endif()

add_subdirectory(bowshock)
add_subdirectory(glad)
