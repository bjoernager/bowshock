// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/save.hxx>

#include <cstdint>
#include <cstring>

auto ::bow::encode_save(void* const buffer_pointer, ::bow::SaveData const& data) noexcept -> void {
	auto buffer = reinterpret_cast<::std::uint8_t*>(buffer_pointer);

	auto const encode_value = [&buffer]<typename T>(T const& val) {
		constexpr ::std::size_t size = sizeof (val);

		::std::memcpy(buffer, &val, size);
		buffer += size;
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
