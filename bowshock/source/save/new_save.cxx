// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/logic.hxx>
#include <bow/save.hxx>

#include <cstdio>
#include <fmt/core.h>

auto ::bow::new_save(::bow::PlayerData& buffer) noexcept -> void {
	::fmt::print(stderr, "generating new save file\n");

	buffer = ::bow::PlayerData {
		.name              = "Caelum\000\000\000\000\000\000\000\000",
		.time              = 0x0u,  // 256 julian years after the Unix Epoch.
		.system_identifier = 0x45u,
		.ship              = {
			.type                = ::bow::ObjectType::Ship,
			.ship_type           = ::bow::Ship::Aquila,
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
			.mass                = ::bow::ship_mass(::bow::Ship::Aquila),
			.next                = nullptr,
		},
		.zoom              = 0x4p0,
	};

	::fmt::print(stderr, "welcome, CMDR {}\n", buffer.name);
}
