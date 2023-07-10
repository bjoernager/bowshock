// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/logic.hxx>
#include <bow/save.hxx>

#include <array>
#include <cstdint>
#include <cstdio>
#include <fmt/core.h>
#include <stdexcept>
#include <string>

auto ::bow::continue_save(::bow::PlayerData& player_data, ::std::string path) -> bool {
	// Return true if save is invalid.

	::fmt::print(stderr, "loading save file at \"{}\"\n", path);

	::std::FILE* file = ::std::fopen(path.c_str(), "r");

	if (file == nullptr) [[unlikely]] {
		::fmt::print(stderr, "unable to open save file\n");

		::bow::new_save(player_data);
		return false;
	}

	::std::array<::std::uint8_t, ::bow::SAVE_LENGTH> raw;

	if (::std::fread(raw.data(), 0x1u, ::bow::SAVE_LENGTH, file) < ::bow::SAVE_LENGTH) [[unlikely]] {
		throw ::std::runtime_error {"unable to read save file"};
	}

	::std::fclose(file);

	::bow::SaveData data;

	::bow::decode_save(data, raw.data());

	if (data.format_version != ::bow::SAVE_VERSION) [[unlikely]] {
		::fmt::print(stderr, "invalid format ({:#04X}) of save file\n", data.format_version);

		return true;
	}
	if (data.ship_type > ::bow::MAX_SHIP_IDENTIFIER) [[unlikely]] {
		::fmt::print(stderr, "invalid ship type ({:#04X})\n", data.ship_type);

		return true;
	}

	player_data = ::bow::PlayerData {
		// Null-terminator is included:
		.name              = "\000\000\000\000\000\000\000\000\000\000\000\000\000",
		.time              = data.time,
		.system_identifier = data.system_identifier,
		.ship              = {
			.type                 = ::bow::ObjectType::Ship,
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
			.mass                 = ::bow::ship_mass(static_cast<::bow::Ship>(data.ship_type)),
			.next                 = nullptr,
		},
		.zoom                     = 0x4p0,
	};

	::std::memcpy(player_data.name, data.commander_name, ::bow::COMMANDER_NAME_LENGTH);
	player_data.name[::bow::COMMANDER_NAME_LENGTH] = '\000';

	::fmt::print(stderr, "welcome back, CMDR {}\n", player_data.name);

	return false;
}
