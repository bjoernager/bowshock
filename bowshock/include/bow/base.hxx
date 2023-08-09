// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#pragma once

#ifndef bow_DATA_DIRECTORY
#error data directory not specified
#endif

#include <atomic>
#include <climits>
#include <cstdint>
#include <exception>
#include <source_location>
#include <string>

static_assert(CHAR_BIT == 0x8, "bytes must contain exactly eight bits");

namespace bow {
	inline ::std::string DATA_DIRECTORY(bow_DATA_DIRECTORY);

	constexpr bool DEBUG = bow_DEBUG;

	constexpr ::std::size_t COMMANDER_NAME_LENGTH = 0x10u;

	constexpr ::std::uint_least8_t NUMBER_OF_QUOTE_IDENTIFIERS = UINT8_C(0x24);

	template<typename T> struct Xyz {
		T x;
		T y;
		T z;
	};

	// UB to use this from an asynchronous signal
	// handler? ISO requires ::std::atomic or
	// ::std::sig_atomic_t, but the former is not
	// lock-free, and the latter is not even truly
	// atomic.
	extern ::std::atomic_flag GOT_INTERRUPT;

	[[noreturn]] auto terminate(::std::string const& location, ::std::string const& message) noexcept -> void;

	// Returns the path to the user's home directory.
	// If we are unable to determine its path, we
	// instead use the current directory ".".
	auto base_directory() noexcept -> ::std::string;
}
