// Copyright 2022-2023 Gabriel Jensen.

#include <bow/lgc.h>

double bow_shipMass([[maybe_unused]] bow_ship const id) {
	double mass = 0x100p0;
	mass /= bow_massMod;
	
	return mass;
}
