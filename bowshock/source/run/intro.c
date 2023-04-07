// Copyright 2022-2023 Gabriel Jensen.

#include <bow/run.h>

#include <GLFW/glfw3.h>
#include <zap/mem.h>

bool bow_intro(bow_gfxDat * const gfxdatptr) {
	bow_log("starting intro");

	bow_gfxDat gfxdat;
	zap_cp(&gfxdat,gfxdatptr,sizeof (gfxdat));

	bool quit = false;
	GLfloat const bowr = 0x1.6D6D6D6Ep-1;
	GLfloat const bowg = 0x1.81818182p-4;
	GLfloat const bowb = 0x1.9999999Ap-3;
	
	glfwSetTime(0x0p0);
	for (double dur = 0x0p0;dur <= 0x3p0;dur = glfwGetTime()) {
		unlikely (bow_pollEvts(&gfxdat)) break;
		
		glClearColor(bowr,bowg,bowb,0x1p0);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(gfxdat.win);
	}
	
	double const fadedur = 0x1p0;
	glfwSetTime(0x0p0);
	for (double fac = 0x0p0;fac <= fadedur;fac = glfwGetTime()) {
		unlikely (bow_pollEvts(&gfxdat)) break;
		
		GLfloat const r = bowr*(0x1p0f-fac/fadedur);
		GLfloat const g = bowg*(0x1p0f-fac/fadedur);
		GLfloat const b = bowb*(0x1p0f-fac/fadedur);
		
		glClearColor(r,g,b,0x1p0);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(gfxdat.win);
	}
	
	glClearColor(0x0p0,0x0p0,0x0p0,0x1p0);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(gfxdat.win);
	
	unlikely (glfwWindowShouldClose(gfxdat.win)) quit = true;
	
	zap_cp(gfxdatptr,&gfxdat,sizeof (gfxdat));
	
	return quit;
}
