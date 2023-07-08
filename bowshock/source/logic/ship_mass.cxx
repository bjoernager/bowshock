// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/logic.hxx>

auto ::bow::ship_mass([[maybe_unused]] ::bow::Ship const identifier) noexcept -> double {
	double mass = 0x100p0;
	mass /= ::bow::MASS_MODIFIER;

	return mass;
}
