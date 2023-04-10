// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.hxx>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

void ::bow::bow::initGfx() noexcept {
	bow_log("initialising graphics");

	bow_logDbg("initialising glfw");
	if (!::glfwInit()) [[unlikely]] {
		bow_logErr("unable to initialise glfw");
		::bow::abrt();
	}

	bow_logDbg("initialising window");
	::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,0x4);
	::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,0x1);
	::glfwWindowHint(GLFW_DECORATED,            GLFW_FALSE);
	::glfwWindowHint(GLFW_OPENGL_PROFILE,       GLFW_OPENGL_CORE_PROFILE);
	::glfwWindowHint(GLFW_RESIZABLE,            GLFW_FALSE);
	::glfwWindowHint(GLFW_SAMPLES,              0x8);
	gfxDat.win = ::glfwCreateWindow(0x400,0x240,"Bowshock",::glfwGetPrimaryMonitor(),nullptr);
	if (gfxDat.win == nullptr) [[unlikely]] {
		bow_logErr("unable to open window");
		::bow::abrt();
	}

	bow_logDbg("initialising context");
	::glfwMakeContextCurrent(gfxDat.win);
	::gladLoadGL();
	glEnable(GL_MULTISAMPLE);
	::GLFWvidmode const * vidmd = ::glfwGetVideoMode(::glfwGetPrimaryMonitor());
	glViewport(0x0,0x0,vidmd->width,vidmd->height);
	glClearColor(0x0p0,0x0p0,0x0p0,0x1p0);
	glClear(GL_COLOR_BUFFER_BIT);
	::glfwSwapBuffers(gfxDat.win);
	::glfwSwapInterval(0x1);

	compShdProg(gfxDat.shdProg,"main");
}
