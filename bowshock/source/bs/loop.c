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
	bow_obj star = {
		.pos  = {
			.x = 0x0p0,
			.y = 0x0p0,
			.z = 0x0p0,
		},
		.typ  = bow_objtyp_star,
		.mass = 0x1'0000'0000p0,
	};
	bow_obj wrld = {
		.pos  = {
			.x = 0x0p0,
			.y = star.pos.y + 0x1'0000p0,
			.z = 0x0p0,
		},
		.typ  = bow_objtyp_wrld,
		.mass = 0x1'0000p0,
	};
	bow_obj sat = {
		.pos  = {
			.x = 0x0p0,
			.y = wrld.pos.y + 0x100u,
			.z = 0x0p0,
		},
		.typ  = bow_objtyp_sat,
		.mass = 0x1p0,
	};
	wrld.vel.x = sqrt(bow_gravconst*star.mass/(wrld.pos.y - star.pos.y)); // orbital speed
	sat.vel.x = wrld.vel.x + sqrt(bow_gravconst*wrld.mass/(sat.pos.y - wrld.pos.y)); // orbital speed
	for (zap_i04 i = 0x0u;;) {
		if (bow_gotintr) {
			bow_log("got interrupt");
			glfwSetWindowShouldClose(bow_gfxdat.win,GLFW_TRUE);
		}
		if (glfwWindowShouldClose(bow_gfxdat.win)) break;
		// Calculate gravitations:
		bow_grav(&star,&wrld);
		bow_grav(&star,&sat);
		bow_grav(&wrld,&star);
		bow_grav(&wrld,&sat);
		bow_grav(&sat, &star);
		bow_grav(&sat, &wrld);
		// Move objects:
		bow_mv(&star);
		bow_mv(&wrld);
		bow_mv(&sat);
		// Plot objects:
		{
			constexpr double frm = 0x4'0000p0;
			zap_i04 const starposx = (zap_i04)((star.pos.x  + frm / 0x2p0) / frm * 0xFFFp0);
			zap_i04 const starposy = (zap_i04)((-star.pos.y + frm / 0x2p0) / frm * 0xFFFp0);
			zap_i04 const wrldposx = (zap_i04)((wrld.pos.x  + frm / 0x2p0) / frm * 0xFFFp0);
			zap_i04 const wrldposy = (zap_i04)((-wrld.pos.y + frm / 0x2p0) / frm * 0xFFFp0);
			zap_i04 const satposx  = (zap_i04)((sat.pos.x   + frm / 0x2p0) / frm * 0xFFFp0);
			zap_i04 const satposy  = (zap_i04)((-sat.pos.y  + frm / 0x2p0) / frm * 0xFFFp0);
			if ((starposx <= 0xFFFu) && (starposy <= 0xFFFu) && (wrldposx <= 0xFFFu) && (wrldposy <= 0xFFFu) && (satposx <= 0xFFFu) && (satposy <= 0xFFFu)) {
				zap_sz const starpos = (starposy * 0xFFFu + starposx) * 0x3u;
				zap_sz const wrldpos = (wrldposy * 0xFFFu + wrldposx) * 0x3u;
				zap_sz const satpos  = (satposy  * 0xFFFu + satposx)  * 0x3u;
				if (img[starpos + 0x0u] <= 0xFEu) img[starpos + 0x0u] += 0x1u;
				if (img[wrldpos + 0x1u] <= 0xFEu) img[wrldpos + 0x1u] += 0x1u;
				if (img[satpos  + 0x2u] <= 0xFEu) img[satpos  + 0x2u] += 0x1u;
			}
		}
		// Check tick number:
		if (i++ == 0xFFFFFu) break;
	}
	{
		zap_i8 * enc;
		zap_sz const enclen = WebPEncodeLosslessRGB((void *)img,0xFFFu,0xFFFu,0xFFFu * 0x3u,&enc);
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
