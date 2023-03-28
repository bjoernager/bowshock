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
	[[maybe_unused]] bow_objroot objroot = { // For miscellaneous objects (canisters, ships...).
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
	bow_obj * const sol = bow_addobj(&sysroot,&objtmp);
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
	bow_obj * const ter = bow_addobj(&sysroot,&objtmp);
	for (;;++playdat.tm) {
		glfwPollEvents();
		if (bow_gotintr) {
			bow_log("got interrupt");
			glfwSetWindowShouldClose(gfxdat.win,GLFW_TRUE);
		}
		if (glfwWindowShouldClose(gfxdat.win)) break;
		// Calculate gravitations:
		//bow_gravobjs(&sysroot);
		bow_grav(ter,sol);
		// Move objects:
		bow_mvobjs(sysroot.objs);
		// Render:
		int frmbufw;
		int frmbufh;
		glfwGetFramebufferSize(gfxdat.win,&frmbufw,&frmbufh);
		GLdouble const vrat = (GLdouble)frmbufh/(GLdouble)frmbufw;
		glViewport(0x0,0x0,frmbufw,frmbufh);
		glOrtho(-0x1p0,0x1p0,-0x1p0,0x1p0,0x0p0,0x0p0);
		double const frm = 0x22'3F8B'93C0p0*0x3p0/0x2p0;
		GLfloat const solposx = (GLfloat)(sol->pos.x/frm);
		GLfloat const solposy = (GLfloat)(sol->pos.y/frm/vrat);
		GLfloat const terposx = (GLfloat)(ter->pos.x/frm);
		GLfloat const terposy = (GLfloat)(ter->pos.y/frm/vrat);
		glClear(GL_COLOR_BUFFER_BIT);
		glPointSize(0x4p0);
		glBegin(GL_POINTS);
		glColor3f(0x1p0,0x0p0,0x0p0);
		glVertex2f(solposx,solposy);
		glColor3f(0x0p0,0x1p0,0x0p0);
		glVertex2f(terposx,terposy);
		glEnd();
		glfwSwapBuffers(gfxdat.win);
	}
	bow_freeobjs(&sysroot);
	zap_cp(gfxdatptr, &gfxdat, sizeof (gfxdat));
	zap_cp(playdatptr,&playdat,sizeof (playdat));
	return bow_stat_ok;
}
