// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/base.hxx>

#include <cstdlib>
#include <cstdio>
#include <fmt/core.h>
#include <string>

auto bow::terminate(::std::string const& location, ::std::string const& message) noexcept -> void {
	::fmt::print(stderr, "[{}] terminate due to: {}\n", location, message);

	::std::abort();
}
