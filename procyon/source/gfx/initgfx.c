#include <acm/gfx.h>

#include <GLFW/glfw3.h>

void acm_initgfx(void) {
	acm_log("Initialising graphics\n");
	if (!glfwInit()) {
		fprintf(stderr,"Unable to initialise GLFW\n");
		acm_exit(acm_stat_err);
	}
	GLFWwindow * win = glfwCreateWindow(0x300,0x200,"Procyon",nullptr,nullptr);
	if (win == nullptr) {
		fprintf(stderr,"Unable to open window\n");
		goto abrt;
	}
	glfwMakeContextCurrent(win);
	acm_dat.win = win;
	return;
abrt:;
	glfwTerminate();
	acm_exit(acm_stat_err);
}
