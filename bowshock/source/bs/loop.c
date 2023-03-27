#define bow_sym "loop"

#include <bow/gfx.h>
#include <bow/lgc.h>
#include <bow/sav.h>

#include <GLFW/glfw3.h>
#include <flux/io.h>
#include <inttypes.h>
#include <math.h>
#include <stdlib.h>
#include <webp/encode.h>
#include <zap/mem.h>

bow_stat bow_loop(bow_playdat * playdatptr) {
	bow_log("entering main loop");
	bow_playdat playdat;
	zap_cp(&playdat,playdatptr,sizeof (playdat));
	zap_sz const imgsz = 0xFFFu * 0xFFFu * 0x3u;
	zap_i8 * img = malloc(imgsz);
	zap_fill(img,0x0u,imgsz);
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
			.z = 0x3.243F'6A89p0,
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
			.x = 0x7652p0,
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
	for (zap_i04 i = 0x0u;;) {
		if (bow_gotintr) {
			bow_log("got interrupt");
			glfwSetWindowShouldClose(bow_gfxdat.win,GLFW_TRUE);
		}
		if (glfwWindowShouldClose(bow_gfxdat.win)) break;
		// Calculate gravitations:
		bow_gravobjs(&sysroot);
		// Move objects:
		bow_mvobjs(sysroot.objs);
		// Plot objects:
		{
			constexpr double frm = 0x22'3F8B'93C0p0*0x3p0;
			zap_i04 const solposx = (zap_i04)(( sol->pos.x+frm/0x2p0)/frm*0xFFFp0);
			zap_i04 const solposy = (zap_i04)((-sol->pos.y+frm/0x2p0)/frm*0xFFFp0);
			zap_i04 const terposx = (zap_i04)(( ter->pos.x+frm/0x2p0)/frm*0xFFFp0);
			zap_i04 const terposy = (zap_i04)((-ter->pos.y+frm/0x2p0)/frm*0xFFFp0);
			if ((solposx <= 0xFFFu) && (solposy <= 0xFFFu) && (terposx <= 0xFFFu) && (terposy <= 0xFFFu)) {
				zap_sz const solpos = (solposy*0xFFFu+solposx)*0x3u;
				zap_sz const terpos = (terposy*0xFFFu+terposx)*0x3u;
				img[solpos+0x0u] = 0xFFu;
				img[terpos+0x1u] = 0xFFu;
			}
		}
		// Check tick number:
		if (i++ == 0x1E18557u * bow_tmmod) break; // One Gregorian year
	}
	bow_freeobjs(&sysroot);
	{
		zap_i8 * enc;
		zap_sz const enclen = WebPEncodeLosslessRGB((void *)img,0xFFFu,0xFFFu,0xFFFu*0x3u,&enc);
		flux_fil * imgfil;
		flux_err err = flux_mkfil(&imgfil,"img.webp",0644u);
		if (err == flux_err_exist) {
			flux_op(&imgfil,"img.webp",flux_md_wr,flux_disc);
		}
		flux_wr(imgfil,enc,enclen);
		flux_cl(imgfil);
		WebPFree(enc);
	}
	free(img);
	zap_cp(playdatptr,&playdat,sizeof (playdat));
	return bow_stat_ok;
}
