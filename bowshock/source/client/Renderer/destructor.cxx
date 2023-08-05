// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/client.hxx>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

bow::Renderer::~Renderer() noexcept {
	delete this->shader_program;

	::glfwDestroyWindow(this->window);
	::glfwTerminate();
}
