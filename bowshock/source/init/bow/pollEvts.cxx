// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.hxx>

#include <GLFW/glfw3.h>

bool ::bow::bow::pollEvts() noexcept {
	::glfwPollEvents();
	
	if (::bow::gotIntr) [[unlikely]] {
		bow_log("got interrupt");
		::glfwSetWindowShouldClose(gfxDat.win,GLFW_TRUE);
	
	}
	if (::glfwWindowShouldClose(gfxDat.win)) [[unlikely]] return true;

	return false;
}
