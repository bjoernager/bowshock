// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/application.hxx>

#include <cstdio>
#include <fmt/core.h>
#include <GLFW/glfw3.h>

auto ::bow::Application::poll_events() noexcept -> bool {
	::glfwPollEvents();

	if (::bow::GOT_INTERRUPT) [[unlikely]] {
		::fmt::print(stderr, "got interrupt\n");
		::glfwSetWindowShouldClose(graphics_data.window, GLFW_TRUE);
	}

	if (::glfwWindowShouldClose(graphics_data.window)) [[unlikely]] { return true; }

	return false;
}
