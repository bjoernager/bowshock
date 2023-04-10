// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.hxx>

#include <GLFW/glfw3.h>

bool ::bow::bow::intro() noexcept {
	bow_log("starting intro");

	bool quit = false;
	GLfloat const bowr = 0x1.6D6D6D6Ep-1;
	GLfloat const bowg = 0x1.81818182p-4;
	GLfloat const bowb = 0x1.9999999Ap-3;
	
	::glfwSetTime(0x0p0);
	for (double dur = 0x0p0;dur <= 0x3p0;dur = ::glfwGetTime()) {
		if (pollEvts()) [[unlikely]] break;
		
		glClearColor(bowr,bowg,bowb,0x1p0);
		glClear(GL_COLOR_BUFFER_BIT);
		::glfwSwapBuffers(gfxDat.win);
	}
	
	double const fadedur = 0x1p0;
	::glfwSetTime(0x0p0);
	for (double fac = 0x0p0;fac <= fadedur;fac = ::glfwGetTime()) {
		if (pollEvts()) [[unlikely]] break;
		
		GLfloat const r = bowr*(0x1p0f-fac/fadedur);
		GLfloat const g = bowg*(0x1p0f-fac/fadedur);
		GLfloat const b = bowb*(0x1p0f-fac/fadedur);
		
		glClearColor(r,g,b,0x1p0);
		glClear(GL_COLOR_BUFFER_BIT);
		::glfwSwapBuffers(gfxDat.win);
	}
	
	glClearColor(0x0p0,0x0p0,0x0p0,0x1p0);
	glClear(GL_COLOR_BUFFER_BIT);
	::glfwSwapBuffers(gfxDat.win);
	
	if (::glfwWindowShouldClose(gfxDat.win)) [[unlikely]] quit = true;
	
	return quit;
}
