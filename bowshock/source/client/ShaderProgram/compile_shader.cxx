// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/client.hxx>

#include <filesystem>
#include <format>
#include <glad/glad.h>
#include <stdexcept>
#include <string>
#include <vector>

using namespace ::std::literals::string_literals;

auto bow::ShaderProgram::compile_shader(::std::string const& name, ::bow::ShaderType const pretty_type) -> ::GLuint {
	// Compile a shader according to the provided
	// shader type. The path of the shader is
	// calculated from the data directory path.

	auto const type = [pretty_type]() -> ::GLuint {
		using ::bow::ShaderType;

		switch (pretty_type) {
		case ShaderType::Fragment:
			return GL_FRAGMENT_SHADER;

		case ShaderType::Geometry:
			return GL_GEOMETRY_SHADER;

		case ShaderType::Vertex:
			return GL_VERTEX_SHADER;
		}
	}();

	auto const type_suffix = [type]() -> ::std::string {
		switch (type) {
		default:
			// Until C++23:
			::__builtin_unreachable();

		case GL_FRAGMENT_SHADER:
			return "frag"s;

		case GL_GEOMETRY_SHADER:
			return "geom"s;

		case GL_VERTEX_SHADER:
			return "vert"s;
		}
	}();

	auto const type_string = [type]() -> ::std::string {
		switch (type) {
		default:
			::__builtin_unreachable();

		case GL_FRAGMENT_SHADER:
			return "fragment"s;

		case GL_GEOMETRY_SHADER:
			return "geometry"s;

		case GL_VERTEX_SHADER:
			return "vertex"s;
		}
	}();

	using ::bow::DATA_DIRECTORY;

	auto const path = DATA_DIRECTORY + "/shaders/"s + name + "." + type_suffix + "."s + ::bow::SHADER_FILE_SUFFIX;

	::bow::log("client"s, ::std::format("compiling {} shader at \"{}\"", type_string, path));

	::std::FILE* file = ::std::fopen(path.c_str(), "r");

	auto const file_size = ::std::filesystem::file_size(path);

	static_assert(sizeof (::GLchar) == sizeof (char));
	auto source = ::std::vector<::GLchar>(file_size + 0x1u);

	if (::std::fread(source.data(), sizeof (::GLchar), file_size, file) < file_size) [[unlikely]] {
		throw ::std::runtime_error("unable to read shader source"s);
	}

	source.push_back('\x00');

	auto const source_pointer = source.data();

	auto shader = glCreateShader(type);
	glShaderSource(shader, 0x1, const_cast<::GLchar const* const*>(&source_pointer), nullptr);

	glCompileShader(shader);

	::GLint compilation_status = 0x0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compilation_status);

	if (compilation_status == GL_FALSE) [[unlikely]] {
		::GLint log_length = 0x0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);

		auto log = new ::GLchar[static_cast<::std::size_t>(log_length)];

		glGetShaderInfoLog(shader, log_length, nullptr, log);

		::bow::log("client"s, "unable to compiler shader:"s);

		::std::fwrite(log, 0x1u, static_cast<::std::size_t>(log_length), stderr);

		delete[] log;

		throw ::std::runtime_error("unable to compile shader"s);
	}

	return shader;
}
