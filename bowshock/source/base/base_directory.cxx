// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/logic.hxx>

#include <cstdlib>
#include <string>

using namespace ::std::literals::string_literals;

auto bow::base_directory() noexcept -> ::std::string {
	auto const pointer = ::std::getenv("HOME");

	if (pointer == nullptr) [[unlikely]] { return "."s; }

	return ::std::string(pointer);
}
