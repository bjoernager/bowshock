// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/logic.hxx>

auto bow::Ship::net_mass() noexcept -> double {
	double mass = 0x1p0 / ::bow::MASS_MODIFIER;

	return mass;
}
