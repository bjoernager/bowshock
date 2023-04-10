// Copyright 2022-2023 Gabriel Jensen.

#include <bow/sav.hxx>

void ::bow::newSav(::bow::plDat & dat) noexcept {
	bow_log("generating new save file");

	dat = ::bow::plDat {
		.nm    = "Caelum\x00\x00\x00\x00\x00\x00\x00\x00",
		.tm    = 0x0u, // 256 julian years after the Unix Epoch.
		.sysId = 0x45u,
		.ship  = {
			.shipTyp = ::bow::ship::aq,
			.pos     = {
				.x = 0x0p0,
				.y = 0x0p0,
				.z = 0x0p0,
			},
			.rot     = {
				.x = 0x0p0,
				.y = 0x0p0,
				.z = 0x0p0,
			},
			.posVel  = {
				.x = 0x0p0,
				.y = 0x0p0,
				.z = 0x0p0,
			},
			.rotVel  = {
				.x = 0x0p0,
				.y = 0x0p0,
				.z = 0x0p0,
			},
		},
	};
	::bow::genDat(dat);
	
	bow_log("welcome, commander %s",dat.nm);
}
