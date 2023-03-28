// Copyright 2022-2023 Gabriel Jensen.

#include <bow/gfx.h>
#include <bow/lgc.h>
#include <bow/sav.h>

#include <GLFW/glfw3.h>
#include <flux/io.h>
#include <inttypes.h>
#include <math.h>
#include <stdlib.h>
#include <zap/mem.h>

bow_stat bow_loop(bow_gfxdat * gfxdatptr,bow_playdat * playdatptr) {
	bow_log("entering main loop");
	bow_gfxdat  gfxdat;
	bow_playdat playdat;
	zap_cp(&gfxdat, gfxdatptr, sizeof (gfxdat));
	zap_cp(&playdat,playdatptr,sizeof (playdat));
	bow_objroot sysroot = { // For stellar bodies.
		.objs = nullptr,
	};
	bow_objroot objroot = { // For miscellaneous objects (canisters, ships...).
		.objs = nullptr,
	};
	bow_obj objtmp = {
		.typ     = bow_objtyp_star,
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
		.mass    = 0x191930A5E75F0C191814000000p0,
		.startyp = bow_star_g,
		// next will be overwritten anyways.
	};
	bow_addobj(&sysroot,&objtmp);
	objtmp = (bow_obj) {
		.typ     = bow_objtyp_wrld,
		.pos     = {
			.x = 0x0p0,
			.y = 0x22'3F8B'93C0p0,
			.z = 0x0p0,
		},
		.rot     = {
			.x = 0x0p0,
			.y = 0x0p0,
			.z = 0x0p0,
		},
		.posvel  = {
			.x = 0x7652p0/bow_tmmod,
			.y = 0x0p0,
			.z = 0x0p0,
		},
		.rotvel  = {
			.x = 0x0p0,
			.y = 0x0p0,
			.z = 0x1.31DB66BBp-15,
		},
		.mass    = 0x4'F0A9'9C58'8848'32A0'0000p0,
		.wrldtyp = bow_wrld_rck,
	};
	bow_addobj(&sysroot,&objtmp);
	objtmp = (bow_obj) {
		.typ     = bow_objtyp_can,
		.pos     = {
			.x = 0x20'0000'0000p0,
			.y = 0x20'0000'0000p0,
			.z = 0x0p0,
		},
		.rot     = {
			.x = 0x0p0,
			.y = 0x0p0,
			.z = 0x0p0,
		},
		.posvel  = {
			.x = 0x16A.09E667F4p0*0x20p0/bow_tmmod,
			.y = 0x0p0,
			.z = 0x0p0,
		},
		.rotvel  = {
			.x = 0x0p0,
			.y = 0x0p0,
			.z = 0x0p0,
		},
		.mass    = 0x1p0,
	};
	bow_addobj(&objroot,&objtmp);
	for (;;++playdat.tm) {
		glfwPollEvents();
		if (bow_gotintr) {
			bow_log("got interrupt");
			glfwSetWindowShouldClose(gfxdat.win,GLFW_TRUE);
		}
		if (glfwWindowShouldClose(gfxdat.win)) break;
		// Calculate gravitations:
		bow_gravsys(&sysroot);
		bow_gravobjs(&sysroot,&objroot);
		// Move objects:
		bow_mvobjs(&sysroot);
		bow_mvobjs(&objroot);
		// Render:
		bow_drw(&gfxdat,&sysroot,&objroot);
	}
	bow_freeobjs(&sysroot);
	zap_cp(gfxdatptr, &gfxdat, sizeof (gfxdat));
	zap_cp(playdatptr,&playdat,sizeof (playdat));
	return bow_stat_ok;
}
