// Copyright 2022-2023 Gabriel Jensen.

#include <bow/sav.hxx>

auto ::bow::newsav(::bow::pldat & dat) noexcept -> void {
	bow_log("generating new save file");

	dat = ::bow::pldat {
		.nam    = "Caelum\x00\x00\x00\x00\x00\x00\x00\x00",
		.tim    = 0x0u, // 256 julian years after the Unix Epoch.
		.sysidt = 0x45u,
		.shp  = {
			.shptyp = ::bow::shp::aqu,
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
	::bow::gendat(dat);
	
	bow_log("welcome, commander %s",dat.nam);
}
