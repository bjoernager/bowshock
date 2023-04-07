// Copyright 2022-2023 Gabriel Jensen.

#include <bow/run.h>

#include <GLFW/glfw3.h>

bool bow_pollEvts(bow_gfxDat * const gfxdat) {
	glfwPollEvents();
	
	unlikely (bow_gotIntr) {
		bow_log("got interrupt");
		glfwSetWindowShouldClose(gfxdat->win,GLFW_TRUE);
	
	}
	unlikely (glfwWindowShouldClose(gfxdat->win)) return true;

	return false;
}
