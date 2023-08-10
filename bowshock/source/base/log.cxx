// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/base.hxx>

#include <cstdio>
#include <fmt/core.h>
#include <string>

auto bow::log(::std::string const& location, ::std::string const& message) noexcept -> void {
	::fmt::print(stderr, "[{}] {}\n", location, message);
}
