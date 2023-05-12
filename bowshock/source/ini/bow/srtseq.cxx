// Copyright 2022-2023 Gabriel Jensen.

#include <bow/ini.hxx>

#include <GLFW/glfw3.h>

auto ::bow::bow::srtseq() noexcept -> bool {
	bow_log("starting start sequence");

	bool exi = false;

	constexpr ::GLfloat bowr = 0x1.6D6D6D6Ep-1;
	constexpr ::GLfloat bowg = 0x1.81818182p-4;
	constexpr ::GLfloat bowb = 0x1.9999999Ap-3;
	
	::glfwSetTime(0x0p0);
	for (::zp::f04 dur = 0x0p0;dur <= 0x3p0;dur = ::glfwGetTime()) {
		if (polevt()) [[unlikely]] break;
		
		glClearColor(bowr,bowg,bowb,0x1p0);
		glClear(GL_COLOR_BUFFER_BIT);
		::glfwSwapBuffers(gfxdat.win);
	}
	
	::zp::f04 const fadedur = 0x1p0;
	::glfwSetTime(0x0p0);
	for (::zp::f04 fac = 0x0p0;fac <= fadedur;fac = ::glfwGetTime()) {
		if (polevt()) [[unlikely]] {break;}
		
		::GLfloat const r = bowr*(0x1p0f-fac/fadedur);
		::GLfloat const g = bowg*(0x1p0f-fac/fadedur);
		::GLfloat const b = bowb*(0x1p0f-fac/fadedur);
		
		glClearColor(r,g,b,0x1p0);
		glClear(GL_COLOR_BUFFER_BIT);
		::glfwSwapBuffers(gfxdat.win);
	}
	
	glClearColor(0x0p0,0x0p0,0x0p0,0x1p0);
	glClear(GL_COLOR_BUFFER_BIT);
	::glfwSwapBuffers(gfxdat.win);
	
	if (::glfwWindowShouldClose(gfxdat.win)) [[unlikely]] {exi = true;}
	
	return exi;
}
