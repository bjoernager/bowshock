// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#pragma once

#include <bow/client.hxx>
#include <bow/server.hxx>

#include <string>
#include <tuple>
#include <vector>

namespace bow {
	template<typename T> struct VersionType {
		T major;
		T minor;
		T patch;
	};

	constexpr ::bow::VersionType<::std::uint64_t> VERSION = {
		.major = 0x0u,
		.minor = 0xCu,
		.patch = 0x0u,
	};

	class Application {
	public:
		explicit Application(int argc, char const* const* argv) noexcept;

		~Application() noexcept;

		auto run() -> int;

	private:
		::bow::ClientConfiguration client_configuration;

		::bow::Client*         client;
		::bow::Server* server;

		[[noreturn]] static auto print_credits() noexcept -> void;

		[[noreturn]] static auto print_help(::std::string const& program_name) noexcept -> void;

		[[nodiscard]] static auto get_quote(::std::uint8_t identifier) -> ::std::tuple<::std::string, ::std::string>;

		auto parse_parameters(::std::string const& program_name, ::std::vector<char const*> const& parameters) -> void;

		auto initialise_signal() -> void;
	};
}
