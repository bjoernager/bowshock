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

static void bow_scrllhandl(GLFWwindow * win,[[maybe_unused]] double const xoff,double const yoff) {
	bow_gfxdat * dat = glfwGetWindowUserPointer(win);
	dat->zoom *= powf(0x1.1p0f,0x0p0f-(float)yoff);
}

void bow_loop(bow_gfxdat * gfxdatptr,bow_playdat * playdatptr) {
	bow_log("entering main loop");
	bow_gfxdat  gfxdat;
	bow_playdat playdat;
	zap_cp(&gfxdat, gfxdatptr, sizeof (gfxdat));
	zap_cp(&playdat,playdatptr,sizeof (playdat));
	glfwSetWindowUserPointer(gfxdat.win,&gfxdat);
	bow_objroot sysroot; // For stellar bodies.
	bow_objroot objroot = { // For miscellaneous objects (canisters, ships...).
		.objs = nullptr,
	};
	bow_gensys(&sysroot,playdat.sysid,playdat.tm);
	bow_obj objtmp = {
		.typ     = bow_objtyp_can,
		.pos     = {
			.x = 0x0p0,
			.y = -0x2p0,
			.z = 0x0p0,
		},
		.rot     = {
			.x = 0x0p0,
			.y = 0x0p0,
			.z = 0x0p0,
		},
		.posvel  = {
			.x = -0x1p-12,
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
	glfwSetScrollCallback(gfxdat.win,bow_scrllhandl);
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
		bow_drw(&gfxdat,&sysroot,&objroot,gfxdat.zoom);
	}
	glfwSetScrollCallback(gfxdat.win,nullptr);
	bow_freeobjs(&sysroot);
	zap_cp(gfxdatptr, &gfxdat, sizeof (gfxdat));
	zap_cp(playdatptr,&playdat,sizeof (playdat));
}
