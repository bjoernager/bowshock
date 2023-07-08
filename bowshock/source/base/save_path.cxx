// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/application.hxx>

#include <cstdio>
#include <cstdlib>
#include <fmt/core.h>
#include <string>

using namespace ::std::literals::string_literals;

auto ::bow::save_path() noexcept -> ::std::string {
	auto base_directory = ::bow::home_directory();

	if (base_directory.empty()) [[unlikely]] {
		::fmt::print(stderr, "unable to get home directory, using current directory\n");

		base_directory = "./"s;
	}

	auto const file_name = ".save_bowshock"s;

	auto const path = base_directory + "/"s + file_name;

	return path;
}
