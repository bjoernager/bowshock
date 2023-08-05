// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/client.hxx>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fmt/core.h>
#include <glad/glad.h>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

using namespace ::std::literals::string_literals;

bow::ShaderProgram::ShaderProgram(::std::string const& name) {
	::fmt::print(stderr, "[client] compiling shader program \"{}\"\n", name);

	// Ignore exceptions:
	auto const vertex_shader   = ::bow::ShaderProgram::compile_shader(name, ::bow::ShaderType::Vertex);
	auto const fragment_shader = ::bow::ShaderProgram::compile_shader(name, ::bow::ShaderType::Fragment);

	this->handle = glCreateProgram();
	glAttachShader(handle, vertex_shader);
	glAttachShader(handle, fragment_shader);
	glLinkProgram(handle);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}
