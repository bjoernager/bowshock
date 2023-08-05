// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/application.hxx>
#include <bow/client.hxx>
#include <bow/server.hxx>


#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fmt/core.h>
#include <stdexcept>
#include <string>
#include <tuple>

auto bow::Application::run() -> int {
	::std::srand(static_cast<int unsigned>(::std::time(nullptr)));

	auto const quote_identifier = static_cast<::std::uint8_t>(::std::rand()) % ::bow::NUMBER_OF_QUOTE_IDENTIFIERS;

	// Print quote:
	{
		auto const quote_source = this->get_quote(quote_identifier);

		auto const quote  = ::std::get<0x0>(quote_source);
		auto const source = ::std::get<0x1>(quote_source);

		::fmt::print("\n{}\n\u2014{}\n\n", quote, source);
	}

	::fmt::print(
		stderr,
		"\x1B[0m\x1B[1mBowshock\x1B[0m {:X}.{:X}.{:X} \u2013 Copyright \u00A9 2022\u20102023 \x1B[1mGabriel Bj\u00F8rnager Jensen\x1B[0m.\n\n",
		::bow::VERSION.major, ::bow::VERSION.minor, ::bow::VERSION.patch
	);

	if constexpr (::bow::DEBUG) {
		::fmt::print("[app] debug mode is enabled\n");
	}

	::fmt::print(stderr, "[app] data directory at \"{}\"\n", ::bow::DATA_DIRECTORY);

	this->initialise_signal();

	// The server handles all of its exceptions.
	this->server = ::bow::Server::start();

	this->client = new ::bow::Client(this->client_configuration);

	// The client handles all of its exceptions.
	this->client->run();

	return 0x0;
}
