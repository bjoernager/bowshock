// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/logic.hxx>

auto bow::hull_mass(::bow::ShipType const ship) noexcept -> double {
	// Calculate the default hull mass of a ship type.
	// This is negated by the ammount of damages hull,
	// whose mass is ignored.

	using ::bow::ShipType;

	double mass = 0x0p0;

	switch (ship) {
	default:
		mass = 0x1p0;
		break;

	case ShipType::Aquila:
		mass = 0x100p0;
	}

	return mass / ::bow::MASS_MODIFIER;
}
