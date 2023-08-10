// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/client.hxx>

#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <string>

using namespace ::std::literals::string_literals;

bow::Renderer::Renderer() {
	::bow::log("client"s, "initialising graphics"s);

	::bow::log("client"s, "initialising glfw"s);

	if (!::glfwInit()) [[unlikely]] {
		throw ::std::runtime_error("unable to initialise glfw"s);
	}

	::bow::log("client"s, "initialising window"s);

	::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 0x4);
	::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0x1);
	::glfwWindowHint(GLFW_DECORATED,             GLFW_FALSE);
	::glfwWindowHint(GLFW_OPENGL_PROFILE,        GLFW_OPENGL_CORE_PROFILE);
	::glfwWindowHint(GLFW_RESIZABLE,             GLFW_FALSE);
	::glfwWindowHint(GLFW_SAMPLES,               0x8);

	this->window = ::glfwCreateWindow(0x400, 0x240, "Bowshock \u2011 Procyon", ::glfwGetPrimaryMonitor(), nullptr);

	if (this->window == nullptr) [[unlikely]] {
		throw ::std::runtime_error("unable to open window"s);
	}

	::bow::log("client"s, "initialising context"s);

	::glfwMakeContextCurrent(this->window);
	::gladLoadGL();

	glEnable(GL_MULTISAMPLE);

	auto const video_mode = ::glfwGetVideoMode(::glfwGetPrimaryMonitor());

	glViewport(0x0, 0x0, video_mode->width, video_mode->height);
	glClearColor(0x0p0, 0x0p0, 0x0p0, 0x1p0);
	glClear(GL_COLOR_BUFFER_BIT);

	::glfwSwapBuffers(this->window);
	::glfwSwapInterval(0x1);

	this->shader_program = new ::bow::ShaderProgram("main"s);

	glGenVertexArrays(0x1, &this->vao);
	glGenBuffers(0x1, &this->vbo);

	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}
