// Copyright 2022-2023 Gabriel Jensen.

#include <bow/gfx.h>
#include <bow/info.h>

#include <GLFW/glfw3.h>
#include <stddef.h>
#include <stdlib.h>
#include <zap/mem.h>

void bow_quit(bow_gfxdat * gfxdatptr,bow_stat const stat) {
	bow_log("quitting");
	bow_gfxdat gfxdat;
	zap_cp(&gfxdat,gfxdatptr,sizeof (gfxdat));
	glfwDestroyWindow(gfxdat.win);
	glfwTerminate();
	int sysstat;
	switch (stat) {
	case bow_stat_err:
		sysstat = EXIT_FAILURE;
		break;
	case bow_stat_ok:
		sysstat = EXIT_SUCCESS;
		break;
	}
	bow_log("goodbye");
	bow_log("exiting with code %i",sysstat);
	exit(sysstat);
}
