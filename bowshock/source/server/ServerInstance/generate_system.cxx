// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/logic.hxx>
#include <bow/server.hxx>

#include <cstdint>
#include <format>
#include <string>

using namespace ::std::literals::string_literals;

auto bow::ServerInstance::generate_system(::bow::ObjectRoot& system, ::std::uint64_t const identifier, ::std::uint64_t const time) -> void {
	::bow::log("server"s, ::std::format("generating system ({:x})", identifier));

	if (system.has_objects()) [[likely]] {
		system.~ObjectRoot();
	}

	// Nb.: The following code is only temporary.
	// Currently, every system has only an Earth-Sol
	// orbit.

	system.add([]() -> ::bow::Star {
		auto star = ::bow::Star();

		star.mass = 0x1p0,
		star.type = ::bow::StarType::G;

		return star;
	}());

	system.add([]() -> ::bow::World {
		auto world = ::bow::World();

		world.position.y            = 0x1.F76F144Dp-1;
		world.positional_velocity.x = 0x1.B2D06FF3p-23 * ::bow::TIME_MODIFIER;
		world.rotational_velocity.z = 0x1.31DB66BBp-15;
		world.mass                  = 0x1.931AFC649369998Fp-19,
		world.type                  = ::bow::WorldType::RockyWorld;

		return world;
	}());

	this->simulate(system, time);
}
