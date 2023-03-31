// Copyright 2022-2023 Gabriel Jensen.

#include <bow/gfx.h>

#include <GLFW/glfw3.h>
#include <math.h>
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
	glfwWindowHint(GLFW_RESIZABLE,            GLFW_FALSE);
	GLFWwindow * win = glfwCreateWindow(0x400,0x240,"Bowshock",glfwGetPrimaryMonitor(),nullptr);
	if (win == nullptr) {
		bow_logerr("unable to open window");
		bow_abrt();
	}
	glfwMakeContextCurrent(win);
	int frmbufw;
	int frmbufh;
	glfwGetFramebufferSize(win,&frmbufw,&frmbufh);
	glViewport(0x0,0x0,frmbufw,frmbufh);
	glOrtho(-0x1p0,0x1p0,-0x1p0,0x1p0,0x0p0,0x0p0);
	glClearColor(0x0p0,0x0p0,0x0p0,0x1p0);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(win);
	glfwSwapInterval(0x1);
	dat.win  = win;
	dat.zoom = 0x4p0f;
	zap_cp(datptr,&dat,sizeof (dat));
}
