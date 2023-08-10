// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/logic.hxx>
#include <bow/server.hxx>

#include <cstdint>
#include <format>
#include <string>

using namespace ::std::literals::string_literals;

auto bow::ServerInstance::simulate(::bow::ObjectRoot& system, ::std::uint64_t const duration) noexcept -> void {
	::bow::log("server"s, ::std::format("simulating for ({}) time units", duration));

	for (auto i = UINT64_C(0x0); i <= duration; ++i) {
		this->gravitate(system);
		this->move(system);
	}
}
