// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/logic.hxx>
#include <bow/server.hxx>

#include <cstdint>
#include <cstdio>
#include <fmt/core.h>

auto bow::ServerInstance::generate_system(::bow::ObjectRoot& system, ::std::uint64_t const identifier, ::std::uint64_t const time) -> void {
	::fmt::print(stderr, "[server] generating system ({:x})\n", identifier);

	if (system.objects != nullptr) [[likely]] {
		this->delete_objects(system);
	}

	// Note: The following code is only temporary;

	auto const star = []() -> ::bow::Star {
		auto star = ::bow::Star();

		star.mass = 0x1p0,
		star.type = ::bow::Star::Type::G;

		return star;
	}();
	this->add_object(system, star);

	auto const world = []() -> ::bow::World {
		auto world = ::bow::World();

		world.position.y            = 0x1.F76F144Dp-1;
		world.positional_velocity.x = 0x1.B2D06FF3p-23 * ::bow::TIME_MODIFIER;
		world.rotational_velocity.z = 0x1.31DB66BBp-15;
		world.mass                  = 0x1.931AFC649369998Fp-19,
		world.type                  = ::bow::World::Type::RockyWorld;

		return world;
	}();
	this->add_object(system, world);

	this->simulate(system, time);
}
