// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/logic.hxx>

auto bow::hull_mass(::bow::ShipType const ship) noexcept -> double {
	using ::bow::ShipType;

	double mass = 0x0p0;

	switch (ship) {
	default:
		mass = 0x1p0;
	case ShipType::Aquila:
		mass = 0x100p0;
	}

	return mass / ::bow::MASS_MODIFIER;
}
