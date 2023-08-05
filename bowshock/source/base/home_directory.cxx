// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/logic.hxx>

#include <cstdio>
#include <cstdlib>
#include <fmt/core.h>
#include <string>

using namespace ::std::literals::string_literals;

auto bow::home_directory() noexcept -> ::std::string {
	auto const pointer = ::std::getenv("HOME");

	if (pointer == nullptr) [[unlikely]] {
		::fmt::print(stderr, "unable to get home directory, using current directory\n");
		return "."s;
	}

	return ::std::string(pointer);
}
