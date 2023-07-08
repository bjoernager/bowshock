// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#pragma once

#include <bow/base.hxx>

#include <cstdint>
#include <source_location>

namespace bow {
	[[noreturn]] auto abort(::std::source_location source_location = ::std::source_location::current()) noexcept -> void;

	auto add_object(::bow::ObjectRoot& root, ::bow::Object const& object) -> void;

	auto delete_objects(::bow::ObjectRoot const& root) noexcept -> void;

	auto generate_system(::bow::ObjectRoot& system, ::std::uint64_t identifier, ::std::uint64_t time) -> void;
}
