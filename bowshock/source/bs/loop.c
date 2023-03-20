#define bow_sym "loop"

#include <bow/gfx.h>
#include <bow/lgc.h>
#include <bow/sav.h>

#include <GLFW/glfw3.h>
#include <inttypes.h>
#include <math.h>
#include <zap/mem.h>

#include <stdio.h>

bow_stat bow_loop(bow_playdat * playdatptr) {
	bow_log("entering main loop");
	FILE * log = fopen("log.xyz","w");
	bow_playdat playdat;
	zap_cp(&playdat,playdatptr,sizeof (playdat));
	bow_obj star0 = {
		.pos  = {
			.x = 0x0.0p0,
			.y = 0x80.0p0,
			.z = 0x0.0p0,
		},
		.typ  = bow_objtyp_star,
		.mass = 0x10000.0p0,
	};
	bow_obj star1 = {
		.pos  = {
			.x = 0x0.0p0,
			.y = -0x80.0p0,
			.z = 0x0.0p0,
		},
		.typ  = bow_objtyp_star,
		.mass = 0x1000.0p0,
	};
	playdat.ship.pos.z = 0x100.0p0;
	star0.vel.x = sqrt(bow_gravconst*star1.mass/0x100.0p0)/0x2.0p0; // orbital speed
	star1.vel.x = -sqrt(bow_gravconst*star0.mass/0x100.0p0)/0x2.0p0; // orbital speed
	bool stop = false;
	for (zap_i04 i = 0x0u;!stop;) {
		if (bow_gotintr) {
			bow_log("got interrupt");
			glfwSetWindowShouldClose(bow_gfxdat.win,GLFW_TRUE);
		}
		if (glfwWindowShouldClose(bow_gfxdat.win)) break;
		// Calculate gravitations:
		bow_grav(&star0,&star1);
		bow_grav(&star1,&star0);
		bow_grav(&playdat.ship,&star0);
		bow_grav(&playdat.ship,&star1);
		// Move objects:
		bow_mv(&star0);
		bow_mv(&star1);
		bow_mv(&playdat.ship);
		// Log:
		//bow_logxyz(playdat.ship.vel);
		fprintf(log,"%f\t%f\t%f\n",star0.pos.x,star0.pos.y,star0.pos.z);
		fprintf(log,"%f\t%f\t%f\n",star1.pos.x,star1.pos.y,star1.pos.z);
		fprintf(log,"%f\t%f\t%f\n",playdat.ship.pos.x,playdat.ship.pos.y,playdat.ship.pos.z);
		// Check tick number:
		if (i++ == 0x7Fu) break;
	}
	fclose(log);
	zap_cp(playdatptr,&playdat,sizeof (playdat));
	return bow_stat_ok;
}
