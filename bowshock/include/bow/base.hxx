// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#pragma once

#ifndef bow_dataDirectory
#error data directory not specified!
#endif

#include <climits>
#include <cstdint>
#include <cstdio>
#include <string>

static_assert(CHAR_BIT == 0x8, "bytes must contain exactly eight bits.");

namespace bow {
	inline ::std::string DATA_DIRECTORY(bow_dataDirectory);

	constexpr ::std::uint8_t NUMBER_OF_QUOTE_IDENTIFIERS = UINT8_C(0x24);

	template<typename T> struct VersionType {
		T major;
		T minor;
		T patch;
	};

	constexpr VersionType<::std::uint64_t> VERSION = {
		.major = 0x0u,
		.minor = 0xCu,
		.patch = 0x0u,
	};

	constexpr bool DEBUG = bow_debug;

	constexpr ::std::size_t COMMANDER_NAME_LENGTH = 0xEu;

	enum struct ObjectType : ::std::uint8_t {
		Canister,
		Player,
		Ship,
		Star,
		Station,
		World, // planet/moon
	};

	enum struct World : ::std::uint8_t {
		Ammonium_world,
		Gas_giant,
		Ice_world,
		Rocky_world,
		Lava_world,
		Water_world,
	};

	enum struct Ship : ::std::uint8_t {
		Aquila,
		Cassiopeia,
		Centaurus,
		Corvus,
		Cursor,
		Eridanus,
		Falco,
		Lyra,
		Taurus,
		Ursa,
		Vipera,
		_max,
	};

	enum struct Star : ::std::uint8_t {
		A, // Main sequence
		B, // Main sequence
		C, // Carbon
		F, // Main sequence
		G, // Main sequence
		K, // Main sequence
		L, // Brown dwarf
		M, // Main sequence
		N, // Neutron star
		O, // Main sequence
		S, // Carbon
		T, // Brown dwarf
		W, // Worm hole
		X, // Black hole
		Y, // Brown dwarf
		Z, // White hole
	};

	enum struct Station : ::std::uint8_t {
		Globus,
		Orbis,
	};

	struct Xyz {
		double x;
		double y;
		double z;
	};

	struct Object {
		::bow::ObjectType type;
		union {
			::bow::World   world_type;
			::bow::Ship    ship_type;
			::bow::Star    star_type;
			::bow::Station station_type;
		};

		::bow::Xyz        position;            // astronomical units
		::bow::Xyz        rotation;            // radians
		::bow::Xyz        positional_velocity; // astronomical units per second
		::bow::Xyz        rotational_velocity; // radians per second
		double            mass;                // kilograms

		::bow::Object*    next;
	};

	struct ObjectRoot {
		::bow::Object* objects;
	};

	struct PlayerData {
		char            name[::bow::COMMANDER_NAME_LENGTH + 0x1u];
		::std::uint64_t time;
		::std::uint64_t system_identifier;
		::bow::Object   ship;
		float           zoom;
	};

	auto object_type_string(::bow::ObjectType type) noexcept -> ::std::string;

	auto random() noexcept -> ::std::uint64_t;

	auto home_directory() noexcept -> ::std::string;
	auto save_path()      noexcept -> ::std::string;
}
