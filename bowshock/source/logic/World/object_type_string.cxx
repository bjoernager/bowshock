// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/logic.hxx>

#include <cstddef>
#include <string>

using namespace ::std::literals::string_literals;

auto bow::World::object_type_string() const noexcept -> ::std::string {
	return "world"s;
}
