// Copyright 2022-2023 Gabriel Jensen.

#include <bow/ini.hxx>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

auto ::bow::bow::inigfx() noexcept -> void {
	bow_log("initialising graphics");

	bow_logdbg("initialising glfw");
	if (!::glfwInit()) [[unlikely]] {
		bow_logerr("unable to initialise glfw");
		::bow::abr();
	}

	bow_logdbg("initialising window");
	::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,0x4);
	::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,0x1);
	::glfwWindowHint(GLFW_DECORATED,            GLFW_FALSE);
	::glfwWindowHint(GLFW_OPENGL_PROFILE,       GLFW_OPENGL_CORE_PROFILE);
	::glfwWindowHint(GLFW_RESIZABLE,            GLFW_FALSE);
	::glfwWindowHint(GLFW_SAMPLES,              0x8);
	gfxdat.win = ::glfwCreateWindow(0x400,0x240,"Bowshock",::glfwGetPrimaryMonitor(),nullptr);
	if (gfxdat.win == nullptr) [[unlikely]] {
		bow_logerr("unable to open window");
		::bow::abr();
	}

	bow_logdbg("initialising context");
	::glfwMakeContextCurrent(gfxdat.win);
	::gladLoadGL();
	glEnable(GL_MULTISAMPLE);
	::GLFWvidmode const * vidmd = ::glfwGetVideoMode(::glfwGetPrimaryMonitor());
	glViewport(0x0,0x0,vidmd->width,vidmd->height);
	glClearColor(0x0p0,0x0p0,0x0p0,0x1p0);
	glClear(GL_COLOR_BUFFER_BIT);
	::glfwSwapBuffers(gfxdat.win);
	::glfwSwapInterval(0x1);

	compshdprg(gfxdat.shdprg,"main");
}
