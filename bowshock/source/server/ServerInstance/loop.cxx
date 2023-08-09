// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/server.hxx>
#include <bow/logic.hxx>

#include <cmath>
#include <cstdio>
#include <fmt/core.h>
#include <stdexcept>

auto bow::ServerInstance::loop() -> void {
	::fmt::print(stderr, "[server] entering main loop\n");

	// For stellar bodies:
	::bow::ObjectRoot system_root = {
		.objects = nullptr,
	};

	// For miscellaneous objects (canisters,  shps...):
	::bow::ObjectRoot objects_root = {
		.objects = nullptr,
	};

	this->generate_system(system_root, 0x0u, 0x0u);

	auto const canister = []() -> ::bow::Canister {
		auto canister = ::bow::Canister();

		canister.position.y            = -0x2p0;
		canister.positional_velocity.x = -0x1p-12;

		return canister;
	}();
	this->add_object(objects_root, canister);

	while (!this->stop_flag->test() && !::bow::GOT_INTERRUPT.test()) {
		this->gravitate(system_root);
		this->gravitate(objects_root, system_root);

		this->move(system_root);
		this->move(objects_root);
	}

	::fmt::print(stderr, "[server] submitting\n");

	this->delete_objects(objects_root);
	this->delete_objects(system_root);
}