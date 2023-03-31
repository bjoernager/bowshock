// Copyright 2022-2023 Gabriel Jensen.

#include <bow/lgc.h>
#include <bow/sav.h>

#include <zap/mem.h>

void bow_rstart(bow_playdat * const datptr) {
	bow_log("restarting save");
	bow_playdat dat = {
		.nm    = "Caelum\x0\x0\x0\x0\x0\x0\x0\x0\x0",
		.sysid = 0x45u,
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
			.posvel  = {
				.x = 0x0p0,
				.y = 0x0p0,
				.z = 0x0p0,
			},
			.rotvel  = {
				.x = 0x0p0,
				.y = 0x0p0,
				.z = 0x0p0,
			},
			.shiptyp = bow_ship_aq,
		},
	};
	bow_log("welcome, commander %s",dat.nm);
	bow_gendat(&dat);
	zap_cp(datptr,&dat,sizeof (dat));
}
