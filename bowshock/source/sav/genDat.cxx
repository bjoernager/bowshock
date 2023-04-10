// Copyright 2022-2023 Gabriel Jensen.

#include <bow/lgc.hxx>
#include <bow/sav.hxx>

void ::bow::genDat(::bow::plDat & dat) noexcept {
	bow_log("generating player data");

	dat.ship.typ  = ::bow::objTyp::ship;
	dat.ship.mass = ::bow::shipMass(dat.ship.shipTyp);
	dat.zoom      = 0x4p0;
}
