// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/client.hxx>

#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <fmt/core.h>
#include <stdexcept>

auto bow::PlayerData::decode_save(::bow::PlayerData & buffer, ::std::array<::std::uint8_t, ::bow::SAVE_LENGTH> const& source) -> void {
	auto data = ::bow::PlayerData::SaveData {
		.format_version             = UINT64_C(0x0),
		.commander_name             = u8"\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
		.time                       = UINT64_C(0x0),
		.system_identifier          = UINT64_C(0x0),
		.ship_type                  = UINT8_C(0x0),
		.ship_position_x            = 0x0p0,
		.ship_position_y            = 0x0p0,
		.ship_position_z            = 0x0p0,
		.ship_rotation_x            = 0x0p0,
		.ship_rotation_y            = 0x0p0,
		.ship_rotation_z            = 0x0p0,
		.ship_positional_velocity_x = 0x0p0,
		.ship_positional_velocity_y = 0x0p0,
		.ship_positional_velocity_z = 0x0p0,
		.ship_rotational_velocity_x = 0x0p0,
		.ship_rotational_velocity_y = 0x0p0,
		.ship_rotational_velocity_z = 0x0p0,
	};

	::std::size_t index = 0x0u;

	auto const decode_value = [&index, &source]<typename T>(T& buffer) {
		constexpr auto size = sizeof (T);

		::std::memcpy(&buffer, &source[index], size);
		index += size;
	};

	decode_value(data.format_version);
	decode_value(data.commander_name);
	decode_value(data.time);
	decode_value(data.system_identifier);
	decode_value(data.ship_type);
	decode_value(data.ship_position_x);
	decode_value(data.ship_position_y);
	decode_value(data.ship_position_z);
	decode_value(data.ship_rotation_x);
	decode_value(data.ship_rotation_y);
	decode_value(data.ship_rotation_z);
	decode_value(data.ship_positional_velocity_x);
	decode_value(data.ship_positional_velocity_y);
	decode_value(data.ship_positional_velocity_z);
	decode_value(data.ship_rotational_velocity_x);
	decode_value(data.ship_rotational_velocity_y);
	decode_value(data.ship_rotational_velocity_z);

	if (data.format_version != ::bow::SAVE_FORMAT_VERSION) [[unlikely]] {
		::fmt::print(stderr, "[client] invalid format ({:#04x}) of save file\n", data.format_version);

		throw ::std::logic_error("invalid format of save file");
	}

	if (data.ship_type > ::bow::MAXIMUM_SHIP_IDENTIFIER) [[unlikely]] {
		::fmt::print(stderr, "[client] invalid ship type ({:#04x})\n", data.ship_type);

		throw ::std::logic_error("invalid ship type");
	}

	buffer.time                       = data.time,
	buffer.system_identifier          = data.system_identifier,
	buffer.ship.type                  = static_cast<::bow::Ship::Type>(data.ship_type),
	buffer.ship.position.x            = data.ship_position_x,
	buffer.ship.position.y            = data.ship_position_y,
	buffer.ship.position.z            = data.ship_position_z,
	buffer.ship.rotation.x            = data.ship_rotation_x,
	buffer.ship.rotation.y            = data.ship_rotation_y,
	buffer.ship.rotation.z            = data.ship_rotation_z,
	buffer.ship.positional_velocity.x = data.ship_positional_velocity_x,
	buffer.ship.positional_velocity.y = data.ship_positional_velocity_y,
	buffer.ship.positional_velocity.z = data.ship_positional_velocity_z,
	buffer.ship.rotational_velocity.x = data.ship_rotational_velocity_x,
	buffer.ship.rotational_velocity.y = data.ship_rotational_velocity_y,
	buffer.ship.rotational_velocity.z = data.ship_rotational_velocity_z,

	buffer.name = ::std::string(reinterpret_cast<char *>(data.commander_name), ::bow::COMMANDER_NAME_LENGTH);
}
