// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/logic.hxx>

auto bow::Ship::net_mass() noexcept -> double {
	double mass = ::bow::hull_mass(this->type);

	return mass;
}
