// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/application.hxx>

#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <vector>

using namespace ::std::literals::string_literals;

auto bow::Application::print_credits() noexcept -> void {
	::std::string path = ::bow::DATA_DIRECTORY + "/CREDITS.txt"s;

	::std::size_t const file_size = ::std::filesystem::file_size(path);

	::std::FILE* file = ::std::fopen(path.c_str(), "r");

	if (file == nullptr) [[unlikely]] {
		::bow::log("app"s, "unable to open credits file"s);
		::std::exit(EXIT_FAILURE);
	}

	auto credits = [file_size]() noexcept -> ::std::vector<char> {
		try {
			return ::std::vector<char>(file_size + 0x2u);
		} catch (...) {
			::bow::log("app"s, "unable to allocate memory for credits"s);
			::std::exit(EXIT_FAILURE);
		}
	}();

	if (::std::fread(&credits.data()[0x1], sizeof (char), file_size, file) < file_size) [[unlikely]] {
		::bow::log("app"s, "unable to read credits file"s);
		::std::exit(EXIT_FAILURE);
	}

	::std::fclose(file);

	credits.front() = '\n';
	credits.back()  = '\n';

	::std::fwrite(credits.data(), sizeof (char), file_size + 0x2u, stdout);

	credits.~vector();

	::std::exit(EXIT_SUCCESS);
}
