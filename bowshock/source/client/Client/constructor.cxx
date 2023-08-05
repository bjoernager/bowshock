// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/client.hxx>
#include <bow/logic.hxx>

#include <cstdio>
#include <filesystem>
#include <fmt/core.h>
#include <string>

using namespace ::std::literals::string_literals;

bow::Client::Client(::bow::ClientConfiguration const& configuration) {
	::fmt::print(stderr, "[client] initialising\n");

	this->configuration = configuration;

	::fmt::print(stderr, "[client] creating configuration directory at {}\n", this->configuration.directory);
	::std::filesystem::create_directory(this->configuration.directory);
	::std::filesystem::create_directory(this->configuration.directory + "/save"s);

	if (this->configuration.new_save) {
		::fmt::print(stderr, "[client] using default save\n");
	} else {
		this->player_data.load(::bow::Client::save_path(this->configuration.directory, this->configuration.save_name));;
	}

	::fmt::print(stderr, "[client] welcome, CMDR {}\n", this->player_data.name);
}
