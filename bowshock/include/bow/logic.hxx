// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#pragma once

#include <bow/base.hxx>

#include <cstdint>
#include <string>
#include <type_traits>

namespace bow {
	// Each of the three main measures (distance, mass,
	// and time) have their own modifier. These
	// modifiers are used to change the "fundamental"
	// units used.

	constexpr double DISTANCE_MODIFIER = 0x1.16A5D2D360000000p037; // 1 astronomical unit
	constexpr double MASS_MODIFIER     = 0x1.91930A5E75F0C192p100; // 1 solar mass
	constexpr double TIME_MODIFIER     = 0x1.0000000000000000p012; // 1 second

	constexpr double GRAVITY_FACTOR = (::bow::MASS_MODIFIER * (::bow::TIME_MODIFIER * ::bow::TIME_MODIFIER)) / ((::bow::DISTANCE_MODIFIER * ::bow::DISTANCE_MODIFIER * ::bow::DISTANCE_MODIFIER)); // Inverse.

	constexpr double GRAVITY_VALUE = 0x1.258688101B4BB16Dp-34 * ::bow::GRAVITY_FACTOR; // gravitational constant (s^2*m*t^2)

	enum struct Ware: ::std::uint8_t {
		AcidsAndBases,
		Air,
		AlcoholicBeverages,
		AncientArtefacts,
		AnimalMeats,
		Atomics,
		Batteries,
		BattleWeapons,
		Beer,
		Biowaste,
		Cameras,
		Cannabis,
		ChemicalWaste,
		Clothing,
		CoffeeAndTea,
		ComputerParts,
		Computers,
		ComputerSoftware,
		Cuttlery,
		Dairy,
		Drones,
		ElectronicComponents,
		EncryptedData,
		EnergyGenerators,
		Explosives,
		Films,
		FruitsAndVegetables,
		Gemstones,
		HandWeapons,
		HullParts,
		Hypnotics,
		Ivory,
		Jewellry,
		Lasers,
		LiveAnimals,
		LuxuryGoods,
		Machinery,
		Magnets,
		Medicine,
		Minerals,
		Money,
		Monitors,
		Music,
		Narcotics,
		NerveAgents,
		NobleGases,
		NobleMetals,
		OrganicDyes,
		Paper,
		Pearls,
		Pesticides,
		Petroleums,
		Pharmaceuticals,
		Pornography,
		Probes,
		ProtiumFuel,
		Radioactives,
		Recyclables,
		Robots,
		Rockets,
		Rubbish,
		ScientificInstruments,
		SkinsAndFurs,
		Slaves,
		Soils,
		Spirits,
		StorageDevices,
		Superconductors,
		SyntheticDyes,
		SyntheticMeat,
		Tobacco,
		TritiumFuel,
		VirtualIntelligences,
		Water,
		Wine,
		XenoRelics,
	};

	enum struct ObjectType: ::std::uint8_t {
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

	enum struct ShipType: ::std::uint8_t {
		Aquila,
		Canis,
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
	constexpr ::std::uint8_t MAXIMUM_SHIP_IDENTIFIER = static_cast<::std::uint8_t>(bow::ShipType::Vipera);

	class Ship final: public ::bow::Object {
	public:
		::bow::ShipType type;

		Ship() noexcept;

		[[nodiscard]] virtual auto object_type_string() const noexcept -> ::std::string;

		[[nodiscard]] auto net_mass() noexcept -> double;
	};

	enum struct StarType: ::std::uint8_t {
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

	class Star final: public ::bow::Object {
	public:
		::bow::StarType type;

		Star() noexcept;

		[[nodiscard]] virtual auto object_type_string() const noexcept -> ::std::string;
	};

	enum struct StationType: ::std::uint8_t {
		Globus,
		Orbis,
	};

	class Station final: public ::bow::Object {
	public:
		::bow::StationType type;

		Station() noexcept;

		[[nodiscard]] virtual auto object_type_string() const noexcept -> ::std::string;
	};

	enum struct WorldType: ::std::uint8_t {
		AmmoniumWorld,
		GasGiant,
		IceWorld,
		LavaWorld,
		RockyWorld,
		WaterWorld,
	};

	class World final: public ::bow::Object {
	public:
		::bow::WorldType type;

		World() noexcept;

		[[nodiscard]] virtual auto object_type_string() const noexcept -> ::std::string;
	};

	[[nodiscard]] auto hull_mass(   ::bow::ShipType ship) noexcept -> double;
	[[nodiscard]] auto ware_density(::bow::Ware     ware) noexcept -> double;
}
