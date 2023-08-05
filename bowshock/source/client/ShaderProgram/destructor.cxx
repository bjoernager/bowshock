// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/client.hxx>

#include <glad/glad.h>

::bow::ShaderProgram::~ShaderProgram() noexcept {
	glDeleteProgram(this->handle);
}
