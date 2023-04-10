// Copyright 2022-2023 Gabriel Jensen.

#include <bow/lgc.hxx>

double ::bow::shipMass([[maybe_unused]] ::bow::ship const id) noexcept {
	double mass = 0x100p0;
	mass /= ::bow::massMod;
	
	return mass;
}
