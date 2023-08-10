// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/client.hxx>

#include <GLFW/glfw3.h>
#include <string>

using namespace ::std::literals::string_literals;

auto bow::Client::poll_events() noexcept -> bool {
	::glfwPollEvents();

	if (::bow::GOT_INTERRUPT.test()) [[unlikely]] {
		::bow::log("client"s, "got interrupt"s);
		::glfwSetWindowShouldClose(renderer.window, GLFW_TRUE);
	}

	if (::glfwWindowShouldClose(renderer.window)) [[unlikely]] { return true; }

	return false;
}
