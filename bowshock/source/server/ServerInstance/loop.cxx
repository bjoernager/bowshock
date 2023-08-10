// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/server.hxx>
#include <bow/logic.hxx>

#include <cmath>
#include <stdexcept>
#include <string>

using namespace ::std::literals::string_literals;

auto bow::ServerInstance::loop() -> void {
	::bow::log("server"s, "entering main loop"s);

	// For stellar bodies:
	auto system_root = ::bow::ObjectRoot();

	// For miscellaneous objects (canisters,  ships, etc.):
	auto objects_root = ::bow::ObjectRoot();

	this->generate_system(system_root, 0x0u, 0x0u);

	objects_root.add([]() -> ::bow::Canister {
		auto canister = ::bow::Canister();

		canister.position.y            = -0x2p0;
		canister.positional_velocity.x = -0x1p-12;

		return canister;
	}());

	while (!this->stop_flag->test() && !::bow::GOT_INTERRUPT.test()) {
		this->gravitate(system_root);
		this->gravitate(objects_root, system_root);

		this->move(system_root);
		this->move(objects_root);
	}

	::bow::log("server"s, "submitting"s);
}
