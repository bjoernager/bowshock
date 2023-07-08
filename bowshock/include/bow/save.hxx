// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#pragma once

#include <bow/base.hxx>

#include <cstddef>
#include <cstdint>
#include <string>

namespace bow {
	constexpr ::std::uint64_t SAVE_VERSION = 0x6u;

	constexpr ::std::size_t SAVE_LENGTH = 0x79u + ::bow::COMMANDER_NAME_LENGTH;

	constexpr ::std::uint8_t MAX_SHIP_IDENTIFIER = static_cast<::std::uint8_t>(::bow::Ship::_max);

	/*
		Save format:

		offset: identifier:                size: format:

		0x00    format_version             8     unsigned
		0x08    commander_name             E     UTF-8
		0x16    time                       8     unsigned
		0x1E    system_identifier          8     unsigned
		0x1F    ship_type                  1     unsigned
		0x27    ship_position_x            8     binary64
		0x2F    ship_position_y            8     binary64
		0x37    ship_position_z            8     binary64
		0x3F    ship_rotation_x            8     binary64
		0x47    ship_rotation_y            8     binary64
		0x4F    ship_rotation_z            8     binary64
		0x57    ship_positional_velocity_x 8     binary64
		0x5F    ship_positional_velocity_y 8     binary64
		0x67    ship_positional_velocity_z 8     binary64
		0x6F    ship_rotational_velocity_x 8     binary64
		0x77    ship_rotational_velocity_y 8     binary64
		0x7F    ship_rotational_velocity_z 8     binary64
	*/

	struct save_data {
		::std::uint64_t format_version;
		char8_t         commander_name[::bow::COMMANDER_NAME_LENGTH];
		::std::uint64_t time;
		::std::uint64_t system_identifier;
		::std::uint8_t  ship_type;
		double          ship_position_x;
		double          ship_position_y;
		double          ship_position_z;
		double          ship_rotation_x;
		double          ship_rotation_y;
		double          ship_rotation_z;
		double          ship_positional_velocity_x;
		double          ship_positional_velocity_y;
		double          ship_positional_velocity_z;
		double          ship_rotational_velocity_x;
		double          ship_rotational_velocity_y;
		double          ship_rotational_velocity_z;
	};

	auto decode_save(::bow::save_data& buf, void const*             data) noexcept -> void;
	auto encode_save(void*             buf, ::bow::save_data const& data) noexcept -> void;

	auto new_save(::bow::PlayerData& data) noexcept -> void;

	auto continue_save(::bow::PlayerData& data, ::std::string file) noexcept -> void;

	auto generate_data(::bow::PlayerData& data) noexcept -> void;

	auto save(::std::string file, ::bow::PlayerData const& data) noexcept -> void;
}
