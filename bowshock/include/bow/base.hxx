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

	constexpr bool DEBUG = bow_debug;

	constexpr ::std::size_t COMMANDER_NAME_LENGTH = 0xEu;

	constexpr ::std::uint8_t NUMBER_OF_QUOTE_IDENTIFIERS = UINT8_C(0x24);

	enum struct ObjectType : ::std::uint8_t {
		Canister,
		Player,
		Ship,
		Star,
		Station,
		World, // planet/moon
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

	enum struct Ware : ::std::uint8_t {
		Air,
		Aluminium,
		AncientArtefacts,
		AnimalFurs,
		AnimalMeat,
		AnimalSkins,
		Atomics,
		BattleWeapons,
		Beer,
		Biowaste,
		Cheese,
		ChemicalWaste,
		Cobalt,
		Coffee,
		ComputerParts,
		Computers,
		Copper,
		Cuttlery,
		Dairy,
		Explosives,
		FruitsAndVegetables,
		Gemstones,
		Gold,
		HandWeapons,
		HullParts,
		HydrogenFuel,
		Iron,
		Ivory,
		Lasers,
		Leather,
		Liquor,
		Lithium,
		LiveAnimals,
		LuxuryGoods,
		Magnets,
		Medicine,
		Minerals,
		Monitors,
		NerveAgents,
		OrganicDyes,
		Paper,
		Pearls,
		Pesticides,
		Platinum,
		Plutonium,
		Radioactives,
		Robots,
		Rockets,
		Rubbish,
		Silver,
		Slaves,
		StorageDevices,
		Superconductors,
		SyntheticMeat,
		Tea,
		Titanium,
		Tobacco,
		TritiumFuel,
		Uranium,
		Water,
		Wine,
		XenoRelics,
	};

	enum struct World : ::std::uint8_t {
		AmmoniumWorld,
		GasGiant,
		IceWorld,
		LavaWorld,
		RockyWorld,
		WaterWorld,
	};

	struct Xyz {
		double x;
		double y;
		double z;
	};

	struct Object {
		::bow::ObjectType type;
		union {
			::bow::Ware    canister_content;
			::bow::Ship    ship_type;
			::bow::Star    star_type;
			::bow::Station station_type;
			::bow::World   world_type;
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
