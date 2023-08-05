// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#pragma once

#include <bow/base.hxx>

#include <cstdint>
#include <string>
#include <type_traits>

namespace bow {
	constexpr double DISTANCE_MODIFIER = 0x1.16A5D2D360000000p037; // 1 astronomical unit
	constexpr double MASS_MODIFIER     = 0x1.91930A5E75F0C192p100; // 1 solar mass
	constexpr double TIME_MODIFIER     = 0x1.0000000000000000p012; // 1 second

	constexpr double GRAVITY_FACTOR = (::bow::MASS_MODIFIER * (::bow::TIME_MODIFIER * ::bow::TIME_MODIFIER)) / ((::bow::DISTANCE_MODIFIER * ::bow::DISTANCE_MODIFIER * ::bow::DISTANCE_MODIFIER)); // Inverse.

	constexpr double GRAVITY_VALUE = 0x1.258688101B4BB16Dp-34 * ::bow::GRAVITY_FACTOR; // gravitational constant (s^2*m*t^2)

	enum struct Ware: ::std::uint8_t {
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

	enum struct ObjectType : ::std::uint8_t {
		Canister,
		Ship,
		Star,
		Station,
		World,
	};

	class Object {
	public:
		::bow::ObjectType object_type;

		::bow::Xyz<double> position;            // astronomical units
		::bow::Xyz<double> rotation;            // radians
		::bow::Xyz<double> positional_velocity; // astronomical units per second
		::bow::Xyz<double> rotational_velocity; // radians per second
		double             mass;                // kilograms

		::bow::Object* next;

		virtual ~Object() noexcept = default;

		[[nodiscard]] virtual auto object_type_string() const noexcept -> ::std::string;

	protected:
		Object() noexcept = default;
	};

	template<typename T>
	concept ObjectLike = ::std::is_base_of_v<::bow::Object, T>;

	class Canister final: public ::bow::Object {
	public:
		::bow::Ware content;

		Canister() noexcept;

		[[nodiscard]] virtual auto object_type_string() const noexcept -> ::std::string;
	};

	class Ship final: public ::bow::Object {
	public:
		enum struct Type: ::std::uint8_t {
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
		};

		::bow::Ship::Type type;

		Ship() noexcept;

		[[nodiscard]] virtual auto object_type_string() const noexcept -> ::std::string;

		[[nodiscard]] auto net_mass() noexcept -> double;
	};
	constexpr ::std::uint8_t MAXIMUM_SHIP_IDENTIFIER = static_cast<::std::uint8_t>(bow::Ship::Type::Vipera);

	class Star final: public ::bow::Object {
	public:
		enum struct Type: ::std::uint8_t {
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

		::bow::Star::Type type;

		Star() noexcept;

		[[nodiscard]] virtual auto object_type_string() const noexcept -> ::std::string;
	};

	class Station final: public ::bow::Object {
	public:
		enum struct Type: ::std::uint8_t {
			Globus,
			Orbis,
		};

		::bow::Station::Type type;

		Station() noexcept;

		[[nodiscard]] virtual auto object_type_string() const noexcept -> ::std::string;
	};

	class World final: public ::bow::Object {
	public:
		enum struct Type: ::std::uint8_t {
			AmmoniumWorld,
			GasGiant,
			IceWorld,
			LavaWorld,
			RockyWorld,
			WaterWorld,
		};

		::bow::World::Type type;

		World() noexcept;

		[[nodiscard]] virtual auto object_type_string() const noexcept -> ::std::string;
	};

	struct ObjectRoot {
		::bow::Object* objects;
	};

	[[nodiscard]] auto ware_mass(::bow::Ware const ware) noexcept -> double;
}
