// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/runtime.hxx>
#include <bow/save.hxx>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fmt/core.h>

auto ::bow::save(::std::string const path, ::bow::PlayerData const& player_data) noexcept -> void {
	using ::bow::SAVE_LENGTH;

	::fmt::print(stderr, "saving CMDR {} at \"{}\"\n", player_data.name, path);

	::std::FILE* file = ::std::fopen(path.c_str(), "w");

	if (file == nullptr) [[unlikely]] {
		::fmt::print(stderr, "unable to open save file\n");

		::std::abort();
	}

	::bow::save_data save_data = {
		.format_version             = ::bow::SAVE_VERSION,
		.time                       = player_data.time,
		.system_identifier          = player_data.system_identifier,
		.ship_type                  = static_cast<::std::uint8_t>(player_data.ship.ship_type),
		.ship_position_x            = player_data.ship.position.x,
		.ship_position_y            = player_data.ship.position.y,
		.ship_position_z            = player_data.ship.position.z,
		.ship_rotation_x            = player_data.ship.rotation.x,
		.ship_rotation_y            = player_data.ship.rotation.y,
		.ship_rotation_z            = player_data.ship.rotation.z,
		.ship_positional_velocity_x = player_data.ship.positional_velocity.x,
		.ship_positional_velocity_y = player_data.ship.positional_velocity.y,
		.ship_positional_velocity_z = player_data.ship.positional_velocity.z,
		.ship_rotational_velocity_x = player_data.ship.rotational_velocity.x,
		.ship_rotational_velocity_y = player_data.ship.rotational_velocity.y,
		.ship_rotational_velocity_z = player_data.ship.rotational_velocity.z,
	};
	::std::memcpy(save_data.commander_name, player_data.name, sizeof (save_data.commander_name));

	::std::uint8_t data[SAVE_LENGTH];

	::bow::encode_save(data, save_data);

	::std::fwrite(data, 0x1u, SAVE_LENGTH, file);
	::std::fclose(file);
}
