// Copyright 2022-2023 Gabriel Jensen.

#include <bow/ini.hxx>

#include <GLFW/glfw3.h>

auto ::bow::bow::polevt() noexcept -> bool {
	::glfwPollEvents();
	
	if (::bow::gotint) [[unlikely]] {
		bow_log("got interrupt");
		::glfwSetWindowShouldClose(gfxdat.win,GLFW_TRUE);
	
	}
	if (::glfwWindowShouldClose(gfxdat.win)) [[unlikely]] return true;

	return false;
}
