#include <acm/bs.h>

#include <GLFW/glfw3.h>
#include <stdlib.h>

void acm_exit(acm_stat const _stat) {
	int const cstat = _stat == acm_stat_ok ? EXIT_SUCCESS : EXIT_FAILURE;
	free((void *)acm_dat.savloc);
	if (acm_dat.gfxisinit) {
		glfwDestroyWindow(acm_dat.win);
		glfwTerminate();
	}
	acm_log("Done (%X)\n",cstat);
	exit(cstat);
}
