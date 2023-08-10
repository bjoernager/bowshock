// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/client.hxx>
#include <bow/logic.hxx>

#include <filesystem>
#include <format>
#include <string>

using namespace ::std::literals::string_literals;

bow::Client::Client(::bow::ClientConfiguration const& configuration) {
	::bow::log("client"s, "initialising"s);

	this->configuration = configuration;

	::bow::log("client"s, ::std::format("creating configuration directory at {}", this->configuration.directory));
	::std::filesystem::create_directory(this->configuration.directory);
	::std::filesystem::create_directory(this->configuration.directory + "/save"s);

	if (this->configuration.new_save) {
		::bow::log("client"s, "using default save"s);
	} else {
		this->player_data.load(::bow::Client::save_path(this->configuration.directory, this->configuration.save_name));;
	}

	::bow::log("client"s, ::std::format("welcome, CMDR {}", this->player_data.name));
}
