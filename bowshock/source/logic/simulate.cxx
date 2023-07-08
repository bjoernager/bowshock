// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/logic.hxx>

#include <bow/runtime.hxx>

#include <cstdio>
#include <fmt/core.h>

auto ::bow::simulate(::bow::ObjectRoot& system, ::std::uint64_t const duration) noexcept -> void {
	::fmt::print(stderr, "simulating for ({}) time units\n", duration);

	for (::std::uint64_t i = 0x0u; i <= duration; ++i) {
		::bow::gravitate(system);
		::bow::move(system);
	}
}
