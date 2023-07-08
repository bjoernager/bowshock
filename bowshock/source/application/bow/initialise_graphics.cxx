// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/application.hxx>

#include <cstdio>
#include <cstdlib>
#include <fmt/core.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

auto ::bow::Application::initialise_graphics() noexcept -> void {
	::fmt::print(stderr, "initialising graphics\n");

	::fmt::print(stderr, "initialising glfw\n");

	if (!::glfwInit()) [[unlikely]] {
		::fmt::print(stderr, "unable to initialise glfw\n");

		::std::abort();
	}

	::fmt::print(stderr, "initialising window\n");

	::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 0x4);
	::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0x1);
	::glfwWindowHint(GLFW_DECORATED,             GLFW_FALSE);
	::glfwWindowHint(GLFW_OPENGL_PROFILE,        GLFW_OPENGL_CORE_PROFILE);
	::glfwWindowHint(GLFW_RESIZABLE,             GLFW_FALSE);
	::glfwWindowHint(GLFW_SAMPLES,               0x8);

	graphics_data.window = ::glfwCreateWindow(0x400, 0x240, "Bowshock", ::glfwGetPrimaryMonitor(), nullptr);

	if (graphics_data.window == nullptr) [[unlikely]] {
		::fmt::print(stderr, "unable to open window");

		::std::abort();
	}

	::fmt::print(stderr, "initialising context\n");

	::glfwMakeContextCurrent(graphics_data.window);
	::gladLoadGL();

	glEnable(GL_MULTISAMPLE);

	::GLFWvidmode const* const video_mode = ::glfwGetVideoMode(::glfwGetPrimaryMonitor());

	glViewport(0x0, 0x0, video_mode->width, video_mode->height);
	glClearColor(0x0p0, 0x0p0, 0x0p0, 0x1p0);
	glClear(GL_COLOR_BUFFER_BIT);

	::glfwSwapBuffers(graphics_data.window);
	::glfwSwapInterval(0x1);

	this->compile_shader_program(graphics_data.shader_program, "main");
}
