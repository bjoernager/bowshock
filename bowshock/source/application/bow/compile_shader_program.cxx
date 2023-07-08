// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/application.hxx>

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

namespace bow {
	static auto compile_shader(::GLuint& shader, ::std::string name, ::GLenum type) -> void;
}

using namespace ::std::literals::string_literals;

static auto ::bow::compile_shader(::GLuint& shader, ::std::string const name, ::GLenum const type) -> void {
	auto const type_suffix = [type]() -> ::std::string {
		switch (type) {
		default: [[unlikely]]
			::fmt::print(stderr, "bad shader type {}\n", static_cast<unsigned int>(type));

			::std::abort();

		case GL_FRAGMENT_SHADER:
			return "frag"s;

		case GL_GEOMETRY_SHADER:
			return "geom"s;

		case GL_TESS_CONTROL_SHADER:
			return "tesc"s;

		case GL_TESS_EVALUATION_SHADER:
			return "tese"s;

		case GL_VERTEX_SHADER:
			return "vert"s;
		}
	}();

	auto const type_string = [type]() -> ::std::string {
		switch (type) {
		default: [[unlikely]]
			::std::abort();

		case GL_FRAGMENT_SHADER:
			return "fragment"s;

		case GL_GEOMETRY_SHADER:
			return "geometry"s;

		case GL_TESS_CONTROL_SHADER:
			return "tesselation control"s;

		case GL_TESS_EVALUATION_SHADER:
			return "tesselation evaluation"s;

		case GL_VERTEX_SHADER:
			return "vertex"s;
		}
	}();

	using ::bow::DATA_DIRECTORY;

	auto path = DATA_DIRECTORY + "/shaders/" + name + "." + type_suffix + "." + ::bow::SHADER_FILE_SUFFIX;

	::fmt::print(stderr, "compiling {} shader at \"{}\"\n", type_string, path);

	::std::FILE* file = ::std::fopen(path.c_str(), "r");

	if (file == nullptr) [[unlikely]] { throw ::std::runtime_error {"unable to open shader source"}; }

	auto const file_size = ::std::filesystem::file_size(path);

	static_assert(::std::is_same_v<GLchar, char>);
	auto source = ::std::vector<GLchar>(file_size + 0x1u);

	::std::fread(source.data(), 0x1u, file_size, file);

	::std::fclose(file);

	source.push_back('\x00');

	auto const source_pointer = source.data();

	shader = glCreateShader(type);
	glShaderSource(shader, 0x1, const_cast<::GLchar const* const*>(&source_pointer), nullptr);

	glCompileShader(shader);

	::GLint compilation_status = 0x0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compilation_status);

	if (compilation_status == GL_FALSE) [[unlikely]] {
		::GLint log_length = 0x0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);

		auto log = new ::GLchar[static_cast<::std::size_t>(log_length)];

		glGetShaderInfoLog(shader, log_length, nullptr, log);

		::fmt::print(stderr, "unable to compiler shader:\n");

		::std::fwrite(log, 0x1u, static_cast<::std::size_t>(log_length), stderr);

		delete[] log;

		throw ::std::runtime_error {"unable to compile shader"};
	}
}

auto ::bow::Application::compile_shader_program(::GLuint& shader_program, ::std::string const name) noexcept -> void {
	::fmt::print(stderr, "compiling shader program \"{}\"\n", name);

	::GLuint vertex_shader;
	::GLuint fragment_shader;

	using ::bow::compile_shader;

	// Ignore exceptions:
	compile_shader(vertex_shader,   name, GL_VERTEX_SHADER);
	compile_shader(fragment_shader, name, GL_FRAGMENT_SHADER);

	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}
