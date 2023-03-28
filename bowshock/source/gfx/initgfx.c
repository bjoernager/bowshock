// Copyright 2022-2023 Gabriel Jensen.

#include <bow/gfx.h>

#include <GLFW/glfw3.h>
#include <zap/mem.h>

void bow_initgfx(bow_gfxdat * const datptr) {
	bow_log("initialising graphics");
	bow_gfxdat dat;
	bow_dbglog("initialising glfw");
	if (!glfwInit()) {
		bow_logerr("unable to initialise glfw");
		bow_abrt();
	}
	bow_dbglog("initialising window");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,0x3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,0x0);
	glfwWindowHint(GLFW_DECORATED,            GLFW_FALSE);
	GLFWwindow * win = glfwCreateWindow(0x300,0x200,"Bowshock",nullptr,nullptr);
	if (win == nullptr) {
		bow_logerr("unable to open window");
		bow_abrt();
	}
	glfwMakeContextCurrent(win);
	glfwSwapInterval(0x1);
	//glClearColor(0x1.6D6D6D6Ep-1,0x1.81818182p-4,0x1.9999999Ap-3,0x1p0);
	glClearColor(0x0p0,0x0p0,0x0p0,0x1p0);
	glClear(GL_COLOR_BUFFER_BIT);
	dat.win = win;
	zap_cp(datptr,&dat,sizeof (dat));
}
