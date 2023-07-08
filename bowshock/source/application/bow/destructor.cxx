// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/application.hxx>

#include <cstdio>
#include <cstdlib>
#include <fmt/core.h>
#include <GLFW/glfw3.h>

::bow::Application::~Application() noexcept {
	::fmt::print(stderr, "quitting\n");

	glDeleteProgram(graphics_data.shader_program);

	::glfwDestroyWindow(graphics_data.window);
	::glfwTerminate();

	::fmt::print(stderr, "Goodbye!\n");
}
