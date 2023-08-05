// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#pragma once

#ifndef BOW_DATA_DIRECTORY
#error data directory not specified!
#endif

#include <atomic>
#include <climits>
#include <cstdint>
#include <string>

static_assert(CHAR_BIT == 0x8, "bytes must contain exactly eight bits.");

namespace bow {
	inline ::std::string DATA_DIRECTORY(BOW_DATA_DIRECTORY);

	constexpr bool DEBUG = BOW_DEBUG;

	constexpr ::std::size_t COMMANDER_NAME_LENGTH = 0x10u;

	constexpr ::std::uint8_t NUMBER_OF_QUOTE_IDENTIFIERS = UINT8_C(0x24);

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

	auto home_directory() noexcept -> ::std::string;
}
