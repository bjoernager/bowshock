// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <math.h>
#include <zap/mem.h>

void bow_initGfx(bow_gfxDat * const datptr) {
	bow_log("initialising graphics");

	bow_gfxDat dat;

	bow_dbgLog("initialising glfw");
	unlikely (!glfwInit()) {
		bow_logErr("unable to initialise glfw");
		bow_abrt();
	}

	bow_dbgLog("initialising window");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,0x4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,0x0);
	glfwWindowHint(GLFW_DECORATED,            GLFW_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE,       GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE,            GLFW_FALSE);
	glfwWindowHint(GLFW_SAMPLES,              0x8);
	GLFWwindow * win = glfwCreateWindow(0x400,0x240,"Bowshock",glfwGetPrimaryMonitor(),nullptr);
	unlikely (win == nullptr) {
		bow_logErr("unable to open window");
		bow_abrt();
	}

	bow_dbgLog("initialising context");
	glfwMakeContextCurrent(win);
	gladLoadGL();
	glEnable(GL_MULTISAMPLE);
	GLFWvidmode const * vidmd = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glViewport(0x0,0x0,vidmd->width,vidmd->height);
	glClearColor(0x0p0,0x0p0,0x0p0,0x1p0);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(win);
	glfwSwapInterval(0x1);

	bow_compShdProg(&dat.shdProg,"main");
	
	dat.win = win;

	zap_cp(datptr,&dat,sizeof (dat));
}
