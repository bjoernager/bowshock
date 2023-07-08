// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#pragma once

#include <bow/runtime.hxx>

#include <csignal>
#include <cstdint>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace bow {
	constexpr ::std::string SHADER_FILE_SUFFIX("glsl");

	struct GraphicsData {
		::GLFWwindow* window;
		::GLuint      shader_program;
	};

	struct TerminalOptions {
		::std::string save_path;
		bool          has_save_path:0x1;
		bool          new_save:0x1;
		bool          skip_intro:0x1;
	};

	class Application {
	public:
		Application() noexcept = default;

		auto run(int argc, char const* const* argv) noexcept -> void;

		~Application() noexcept;

	private:
		::bow::PlayerData   player_data;
		::bow::GraphicsData graphics_data;

		auto get_quote(::std::string& quote, ::std::string& source, ::std::uint8_t code) noexcept -> void;

		auto print_quote() noexcept -> void;

		[[noreturn]] auto print_credits() noexcept -> void;

		[[noreturn]] auto print_help(::std::string program_name) noexcept -> void;

		auto check_parameters(TerminalOptions& options, int argc, char const* const* argv) noexcept -> void;

		auto compile_shader_program(::GLuint& shader_program, ::std::string name) noexcept -> void;

		auto initialise_graphics() noexcept -> void;
		auto initialise_random()   noexcept -> void;
		auto initialise_signal()   noexcept -> void;

		auto poll_events() noexcept -> bool;

		auto start_sequence() noexcept -> bool;

		auto loop() noexcept -> void;
	};

	extern ::std::sig_atomic_t volatile GOT_INTERRUPT;
}
