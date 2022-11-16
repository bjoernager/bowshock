#include <acm/sav.h>

#include <flux.h>
#include <inttypes.h>
#include <stdio.h>

int main(int const argc,[[maybe_unused]] char const * const * const argv) {
	acm_dat.gfxisinit = false;
	if (argc > 0x1) {
		fprintf(stderr,"Ignoring terminal options\n");
	}
	printf("Procyon, %" PRIxLEAST64 " - Copyright 2022 Gabriel Jensen.\n",acm_ver);
	acm_init();
	acm_cont(&acm_dat.pldat);
	acm_log("Ready\n");
	while (!glfwWindowShouldClose(acm_dat.win)) {
		if (acm_gotintr) {
			fprintf(stderr,"Got interrupt, stopping\n");
			glfwSetWindowShouldClose(acm_dat.win,0x1);
		}
	}
	acm_sav(&acm_dat.pldat);
	acm_exit(acm_stat_ok);
}
