// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/save.hxx>

#include <cstdint>
#include <cstdio>
#include <fmt/core.h>
#include <string>

auto ::bow::continue_save(::bow::PlayerData& player_data, ::std::string path) noexcept -> void {
	::fmt::print(stderr, "loading save file at \"{}\"\n", path);

	::std::FILE* file = ::std::fopen(path.c_str(), "r");

	if (file == nullptr) [[unlikely]] {
		::fmt::print(stderr, "unable to open save file\n");

		return ::bow::new_save(player_data);
	}

	::std::uint8_t raw_data[::bow::SAVE_LENGTH];

	::std::fread(raw_data, 0x1u, ::bow::SAVE_LENGTH, file);
	::std::fclose(file);

	::bow::save_data data;

	::bow::decode_save(data, raw_data);

	if (data.format_version != ::bow::SAVE_VERSION) [[unlikely]] {
		::fmt::print(stderr, "invalid format ({:#04X}) of save file\n", data.format_version);

		return ::bow::new_save(player_data);
	}
	if (data.ship_type > ::bow::MAX_SHIP_IDENTIFIER) [[unlikely]] {
		::fmt::print(stderr, "invalid ship type ({:#04X})\n", data.ship_type);

		return ::bow::new_save(player_data);
	}

	player_data = ::bow::PlayerData {
		.time              = data.time,
		.system_identifier = data.system_identifier,
		.ship              = {
			.ship_type            = static_cast<::bow::Ship>(data.ship_type),
			.position             = {
				.x   = data.ship_position_x,
				.y   = data.ship_position_y,
				.z   = data.ship_position_z,
			},
			.rotation             = {
				.x   = data.ship_rotation_x,
				.y   = data.ship_rotation_y,
				.z   = data.ship_rotation_z,
			},
			.positional_velocity  = {
				.x   = data.ship_positional_velocity_x,
				.y   = data.ship_positional_velocity_y,
				.z   = data.ship_positional_velocity_z,
			},
			.rotational_velocity  = {
				.x   = data.ship_rotational_velocity_x,
				.y   = data.ship_rotational_velocity_y,
				.z   = data.ship_rotational_velocity_z,
			},
		},
	};

	::std::memcpy(player_data.name, data.commander_name, ::bow::COMMANDER_NAME_LENGTH);
	player_data.name[::bow::COMMANDER_NAME_LENGTH] = '\000';

	::bow::generate_data(player_data);

	::fmt::print(stderr, "welcome back, CMDR {}\n", player_data.name);
}
