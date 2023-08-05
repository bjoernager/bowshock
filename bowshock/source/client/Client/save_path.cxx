// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/client.hxx>

#include <string>

using namespace ::std::literals::string_literals;

auto bow::Client::save_path(::std::string const& directory, ::std::string const& name) noexcept -> ::std::string {
	auto const path = directory + "/save/"s + name + ".bowshock"s;

	return path;
}
