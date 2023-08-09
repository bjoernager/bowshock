// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/application.hxx>

#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fmt/core.h>
#include <stdexcept>

auto bow::Application::print_credits() noexcept -> void {
	::std::string path = ::bow::DATA_DIRECTORY + "/CREDITS.txt";

	::std::size_t const file_size = ::std::filesystem::file_size(path);

	::std::FILE* file = ::std::fopen(path.c_str(), "r");

	if (file == nullptr) [[unlikely]] {
		::fmt::print(stderr, "[app] unable to open credits file\n");

		::std::exit(EXIT_FAILURE);
	}

	::std::string credits;

	try {
		credits.reserve(file_size);
	} catch (...) {
		::fmt::print(stderr, "[app] unable to allocate memory for credits\n");

		::std::exit(EXIT_FAILURE);
	}

	::std::fread(credits.data(), 0x1u, file_size, file);
	::std::fclose(file);

	credits.append("\n");

	::std::fputs(credits.c_str(), stdout);

	credits.~basic_string();

	::std::exit(EXIT_SUCCESS);
}