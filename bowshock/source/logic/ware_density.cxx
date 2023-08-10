// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/logic.hxx>

auto bow::ware_density([[maybe_unused]] ::bow::Ware const ware) noexcept -> double {
	double mass = 0x1p0;

	return mass / ::bow::MASS_MODIFIER;
}
