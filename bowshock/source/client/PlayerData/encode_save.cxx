// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/client.hxx>

#include <array>
#include <cstdint>
#include <cstring>

auto bow::PlayerData::encode_save(::std::array<::std::uint8_t, ::bow::SAVE_LENGTH>& buffer, ::bow::PlayerData const& source) noexcept -> void {
	auto data = ::bow::PlayerData::SaveData {
		.format_version             = ::bow::SAVE_FORMAT_VERSION,
		.commander_name             = u8"\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
		.time                       = source.time,
		.system_identifier          = source.system_identifier,
		.ship_type                  = static_cast<::std::uint8_t>(source.ship.type),
		.ship_position_x            = source.ship.position.x,
		.ship_position_y            = source.ship.position.y,
		.ship_position_z            = source.ship.position.z,
		.ship_rotation_x            = source.ship.rotation.x,
		.ship_rotation_y            = source.ship.rotation.y,
		.ship_rotation_z            = source.ship.rotation.z,
		.ship_positional_velocity_x = source.ship.positional_velocity.x,
		.ship_positional_velocity_y = source.ship.positional_velocity.y,
		.ship_positional_velocity_z = source.ship.positional_velocity.z,
		.ship_rotational_velocity_x = source.ship.rotational_velocity.x,
		.ship_rotational_velocity_y = source.ship.rotational_velocity.y,
		.ship_rotational_velocity_z = source.ship.rotational_velocity.z,
	};

	::std::memcpy(&data.commander_name, source.name.data(), ::bow::COMMANDER_NAME_LENGTH);

	::std::size_t index = 0x0u;

	auto const encode_value = [&buffer, &index]<typename T>(T const& value) {
		constexpr auto size = sizeof (T);

		::std::memcpy(&buffer[index], &value, size);
		index += size;
	};

	encode_value(data.format_version);
	encode_value(data.commander_name);
	encode_value(data.time);
	encode_value(data.system_identifier);
	encode_value(data.ship_type);
	encode_value(data.ship_position_x);
	encode_value(data.ship_position_y);
	encode_value(data.ship_position_z);
	encode_value(data.ship_rotation_x);
	encode_value(data.ship_rotation_y);
	encode_value(data.ship_rotation_z);
	encode_value(data.ship_positional_velocity_x);
	encode_value(data.ship_positional_velocity_y);
	encode_value(data.ship_positional_velocity_z);
	encode_value(data.ship_rotational_velocity_x);
	encode_value(data.ship_rotational_velocity_y);
	encode_value(data.ship_rotational_velocity_z);
}
