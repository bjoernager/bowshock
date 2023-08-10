// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#pragma once

#include <bow/logic.hxx>

#include <array>
#include <csignal>
#include <cstdint>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace bow {
	constexpr ::std::uint64_t SAVE_FORMAT_VERSION = 0x7u;

	constexpr ::std::size_t SAVE_LENGTH = 0x79u + ::bow::COMMANDER_NAME_LENGTH;

	constexpr ::std::string SHADER_FILE_SUFFIX("glsl");

	/*
		Save format:

		offset: identifier:                size: format:

		0x00    format_version             8     unsigned
		0x08    commander_name             E     UTF-8
		0x16    time                       8     unsigned
		0x1E    system_identifier          8     unsigned
		0x1F    ship_type                  1     unsigned
		0x27    ship_position_x            8     binary64
		0x2F    ship_position_y            8     binary64
		0x37    ship_position_z            8     binary64
		0x3F    ship_rotation_x            8     binary64
		0x47    ship_rotation_y            8     binary64
		0x4F    ship_rotation_z            8     binary64
		0x57    ship_positional_velocity_x 8     binary64
		0x5F    ship_positional_velocity_y 8     binary64
		0x67    ship_positional_velocity_z 8     binary64
		0x6F    ship_rotational_velocity_x 8     binary64
		0x77    ship_rotational_velocity_y 8     binary64
		0x7F    ship_rotational_velocity_z 8     binary64
	*/

	struct ClientConfiguration final {
		::std::string         directory;
		::std::string         save_name;
		::std::uint_least16_t network_port;
		bool                  new_save:            0x1;
		bool                  skip_start_sequence: 0x1;
	};

	class PlayerData final {
	public:
		::std::string   name;
		::std::uint64_t time;
		::std::uint64_t system_identifier;
		::bow::Ship     ship;
		float           zoom;

		PlayerData()                          noexcept;
		PlayerData(::std::string const& path);

		auto save(::std::string const& path) -> void;
		auto load(::std::string const& path) -> void;

	private:
		struct SaveData {
			::std::uint64_t format_version;
			char8_t         commander_name[::bow::COMMANDER_NAME_LENGTH];
			::std::uint64_t time;
			::std::uint64_t system_identifier;
			::std::uint8_t  ship_type;
			double          ship_position_x;
			double          ship_position_y;
			double          ship_position_z;
			double          ship_rotation_x;
			double          ship_rotation_y;
			double          ship_rotation_z;
			double          ship_positional_velocity_x;
			double          ship_positional_velocity_y;
			double          ship_positional_velocity_z;
			double          ship_rotational_velocity_x;
			double          ship_rotational_velocity_y;
			double          ship_rotational_velocity_z;
		};

		auto encode_save(::std::array<::std::uint8_t, ::bow::SAVE_LENGTH>& buffer, ::bow::PlayerData const& source) noexcept -> void;

		auto decode_save(::bow::PlayerData & buffer, ::std::array<::std::uint8_t, ::bow::SAVE_LENGTH> const& source) -> void;

		auto write_file(::std::string const& path, ::std::array<::std::uint8_t, ::bow::SAVE_LENGTH> const& buffer) -> void;

		auto read_file(::std::array<::std::uint8_t, ::bow::SAVE_LENGTH>& buffer, ::std::string const& path) -> bool;
	};

	enum struct ShaderType {
		Fragment,
		Geometry,
		Vertex,
	};

	class ShaderProgram final {
	public:
		::GLuint handle;

		ShaderProgram() noexcept = default;

		explicit ShaderProgram(::std::string const& name);

		~ShaderProgram() noexcept;

	private:
		static auto compile_shader(::std::string const& name, ::bow::ShaderType type) -> ::GLuint;
	};

	class Renderer final {
	public:
		::GLFWwindow*         window;
		::bow::ShaderProgram* shader_program;
		::GLuint              vao;
		::GLuint              vbo;

		Renderer();

		~Renderer() noexcept;

		auto render(::GLfloat const vertices[], ::std::size_t size) -> void;
	};

	class Client final {
	public:
		explicit Client(::bow::ClientConfiguration const& configuration);

		~Client() noexcept;

		static auto save_path(::std::string const& directory, ::std::string const& name) noexcept -> ::std::string;

		auto run() noexcept -> void;

	private:
		::bow::ClientConfiguration configuration;

		::bow::PlayerData player_data;

		::bow::Renderer renderer;

		auto poll_events() noexcept -> bool;

		auto start_sequence() -> bool;

		auto loop() -> void;
	};
}
