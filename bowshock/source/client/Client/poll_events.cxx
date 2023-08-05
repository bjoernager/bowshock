// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/client.hxx>

#include <cstdio>
#include <fmt/core.h>
#include <GLFW/glfw3.h>

auto bow::Client::poll_events() noexcept -> bool {
	::glfwPollEvents();

	if (::bow::GOT_INTERRUPT.test()) [[unlikely]] {
		::fmt::print(stderr, "got interrupt\n");
		::glfwSetWindowShouldClose(renderer.window, GLFW_TRUE);
	}

	if (::glfwWindowShouldClose(renderer.window)) [[unlikely]] { return true; }

	return false;
}
