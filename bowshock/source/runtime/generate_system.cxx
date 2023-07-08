// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/logic.hxx>
#include <bow/runtime.hxx>

#include <cstdint>
#include <cstdio>
#include <fmt/core.h>

auto ::bow::generate_system(::bow::ObjectRoot& system, ::std::uint64_t const identifier, ::std::uint64_t const time) -> void {
	::fmt::print(stderr, "generating system ({:X})\n", identifier);

	// Note: The following code is only temporary;
	system.objects = nullptr;
	::bow::Object objTmp;
	objTmp = ::bow::Object {
		.type                = ::bow::ObjectType::Star,
		.star_type           = ::bow::Star::G,
		.position            = {
			.x = 0x0p0,
			.y = 0x0p0,
			.z = 0x0p0,
		},
		.rotation            = {
			.x = 0x0p0,
			.y = 0x0p0,
			.z = 0x0p0,
		},
		.positional_velocity = {
			.x = 0x0p0,
			.y = 0x0p0,
			.z = 0x0p0,
		},
		.rotational_velocity = {
			.x = 0x0p0,
			.y = 0x0p0,
			.z = 0x0p0,
		},
		.mass                = 0x1p0,
		// next will be overwritten anyways.
	};
	::bow::add_object(system, objTmp);

	objTmp = ::bow::Object {
		.type                 = ::bow::ObjectType::World,
		.world_type           = ::bow::World::Rocky_world,
		.position             = {
			.x = 0x0p0,
			.y = 0x1.F76F144Dp-1,
			.z = 0x0p0,
		},
		.rotation             = {
			.x = 0x0p0,
			.y = 0x0p0,
			.z = 0x0p0,
		},
		.positional_velocity  = {
			.x = 0x1.B2D06FF3p-23*::bow::TIME_MODIFIER,
			.y = 0x0p0,
			.z = 0x0p0,
		},
		.rotational_velocity  = {
			.x = 0x0p0,
			.y = 0x0p0,
			.z = 0x1.31DB66BBp-15,
		},
		.mass                 = 0x1.931AFC649369998Fp-19,
	};
	::bow::add_object(system, objTmp);

	::bow::simulate(system, time);
}
