// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/logic.hxx>
#include <bow/server.hxx>

#include <cstdint>
#include <cstdio>
#include <fmt/core.h>

auto bow::ServerInstance::simulate(::bow::ObjectRoot& system, ::std::uint64_t const duration) noexcept -> void {
	::fmt::print(stderr, "[server] simulating for ({}) time units\n", duration);

	for (auto i = UINT64_C(0x0); i <= duration; ++i) {
		this->gravitate(system);
		this->move(system);
	}
}
