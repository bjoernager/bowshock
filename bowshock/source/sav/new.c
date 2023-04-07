// Copyright 2022-2023 Gabriel Jensen.

#include <bow/sav.h>

#include <zap/mem.h>

void bow_new(bow_plDat * const datptr) {
	bow_log("generating new save file");

	bow_plDat dat = {
		.nm    = "Caelum\x00\x00\x00\x00\x00\x00\x00\x00\x00",
		.sysId = 0x45u,
		.tm    = 0x0u, // 256 julian years after the Unix Epoch.
		.ship  = {
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
			.shipTyp = bow_ship_aq,
		},
	};
	bow_genDat(&dat);
	
	bow_log("welcome, commander %s",dat.nm);

	zap_cp(datptr,&dat,sizeof (dat));
}
