#define bow_sym "quit"

#include <bow/gfx.h>
#include <bow/info.h>

#include <GLFW/glfw3.h>
#include <stdlib.h>

void bow_quit(bow_stat const stat) {
	bow_log("quitting");
	glfwDestroyWindow(bow_gfxdat.win);
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
