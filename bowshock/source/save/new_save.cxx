// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/save.hxx>

#include <cstdio>
#include <fmt/core.h>

auto ::bow::new_save(::bow::PlayerData& data) noexcept -> void {
	::fmt::print(stderr, "generating new save file\n");

	data = ::bow::PlayerData {
		.name              = "Caelum\x00\x00\x00\x00\x00\x00\x00\x00",
		.time              = 0x0u,  // 256 julian years after the Unix Epoch.
		.system_identifier = 0x45u,
		.ship  = {
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
		},
	};
	::bow::generate_data(data);

	::fmt::print(stderr, "welcome, CMDR {}\n", data.name);
}
