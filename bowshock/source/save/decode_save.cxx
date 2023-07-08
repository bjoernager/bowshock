// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/save.hxx>

#include <cstdint>
#include <cstring>

auto ::bow::decode_save(::bow::save_data& buffer, void const* data_pointer) noexcept -> void {
	auto data = reinterpret_cast<::std::uint8_t const*>(data_pointer);

	auto const decode_value = [&data]<typename T>(T& buffer) {
		constexpr ::std::size_t size = sizeof (buffer);

		::std::memcpy(&buffer, data, size);
		data += size;
	};

	decode_value(buffer.format_version);
	decode_value(buffer.commander_name);
	decode_value(buffer.time);
	decode_value(buffer.system_identifier);
	decode_value(buffer.ship_type);
	decode_value(buffer.ship_position_x);
	decode_value(buffer.ship_position_y);
	decode_value(buffer.ship_position_z);
	decode_value(buffer.ship_rotation_x);
	decode_value(buffer.ship_rotation_y);
	decode_value(buffer.ship_rotation_z);
	decode_value(buffer.ship_positional_velocity_x);
	decode_value(buffer.ship_positional_velocity_y);
	decode_value(buffer.ship_positional_velocity_z);
	decode_value(buffer.ship_rotational_velocity_x);
	decode_value(buffer.ship_rotational_velocity_y);
	decode_value(buffer.ship_rotational_velocity_z);
}
