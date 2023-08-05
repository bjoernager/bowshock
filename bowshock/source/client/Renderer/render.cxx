// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/client.hxx>
#include <bow/logic.hxx>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

auto bow::Renderer::render(::GLfloat const vertices[], ::std::size_t const size) -> void {
	glClearColor(0x0p0f, 0x0p0f, 0x0p0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0x0, size, vertices);

	glUseProgram(this->shader_program->handle);

	glBindVertexArray(this->vao);
	glDrawArrays(GL_TRIANGLES, 0x0, 0x3 * 0x1);

	::glfwSwapBuffers(this->window);
}
