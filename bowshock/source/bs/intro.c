// Copyright 2022-2023 Gabriel Jensen.

#include <bow/gfx.h>
#include <bow/lgc.h>

#include <GLFW/glfw3.h>
#include <zap/mem.h>

bool bow_intro(bow_gfxdat * const gfxdatptr) {
	bow_log("starting intro");
	bow_gfxdat gfxdat;
	zap_cp(&gfxdat,gfxdatptr,sizeof (gfxdat));
	bool quit = false;
	GLfloat const bowr = 0x1.6D6D6D6Ep-1;
	GLfloat const bowg = 0x1.81818182p-4;
	GLfloat const bowb = 0x1.9999999Ap-3;
	glClearColor(bowr,bowg,bowb,0x1p0);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(gfxdat.win);
	glfwSetTime(0x0p0);
	for (double dur = 0x0p0;dur <= 0x3p0;dur = glfwGetTime()) {
		glfwPollEvents();
		if (bow_gotintr) {
			bow_log("got interrupt");
			glfwSetWindowShouldClose(gfxdat.win,GLFW_TRUE);
		}
		if (glfwWindowShouldClose(gfxdat.win)) break;
	}
	double const fadedur = 0x1p0;
	glfwSetTime(0x0p0);
	for (double fac = 0x0p0;fac <= fadedur;fac = glfwGetTime()) {
		glfwPollEvents();
		if (bow_gotintr) {
			bow_log("got interrupt");
			glfwSetWindowShouldClose(gfxdat.win,GLFW_TRUE);
		}
		if (glfwWindowShouldClose(gfxdat.win)) break;
		GLfloat const r = bowr-fac/fadedur;
		GLfloat const g = bowg-fac/fadedur;
		GLfloat const b = bowb-fac/fadedur;
		glClearColor(r,g,b,0x1p0);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(gfxdat.win);
	}
	glClearColor(0x0p0,0x0p0,0x0p0,0x1p0);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(gfxdat.win);
	if (glfwWindowShouldClose(gfxdat.win)) quit = true;
	zap_cp(gfxdatptr,&gfxdat,sizeof (gfxdat));
	return quit;
}
