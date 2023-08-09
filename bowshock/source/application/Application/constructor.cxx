// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/application.hxx>
#include <bow/client.hxx>
#include <bow/network.hxx>

#include <cstdio>
#include <cstdlib>
#include <fmt/core.h>
#include <string>
#include <vector>

using namespace ::std::literals::string_literals;

bow::Application::Application(int const argc, char const* const* const argv) noexcept {
	::fmt::print(stderr, "[app] configuring application\n");

	auto const program_name = [&argc, argv]() -> ::std::string {
		if (argc < 0x1) [[unlikely]] {
			::bow::terminate("app", "program not provided");
		} else {
			return ::std::string(*argv);
		}
	}();

	this->client_configuration = ::bow::ClientConfiguration {
		.directory           = ""s,
		.save_name           = "save"s,
		.network_port        = ::bow::DEFAULT_NETWORK_PORT,
		.new_save            = false,
		.skip_start_sequence = false,
	};

	this->server_configuration = ::bow::ServerConfiguration {
		.network_port = ::bow::DEFAULT_NETWORK_PORT,
	};

	this->client =nullptr;
	this->server =nullptr;

	::std::vector<char const*> parameters(argv + 0x1u, argv + static_cast<::std::size_t>(argc));

	this->parse_parameters(program_name, parameters);

	if (this->client_configuration.directory.empty()) [[likely]] {
		auto const base_directory = ::bow::base_directory();

		this->client_configuration.directory = base_directory + "/.bowshock"s;
	}
}
