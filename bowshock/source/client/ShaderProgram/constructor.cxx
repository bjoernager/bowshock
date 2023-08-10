// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/client.hxx>

#include <format>
#include <glad/glad.h>
#include <string>

using namespace ::std::literals::string_literals;

bow::ShaderProgram::ShaderProgram(::std::string const& name) {
	// Compile a shader program. Currently, this means
	// compiling a vertex shader and an equivalent
	// fragment shader, both with the name "name". Cf.
	// compile_shader for more information.

	::bow::log("client"s, ::std::format("compiling shader program \"{}\"", name));

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
