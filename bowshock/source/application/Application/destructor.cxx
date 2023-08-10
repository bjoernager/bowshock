// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/application.hxx>

#include <fmt/core.h>
#include <string>

using namespace ::std::literals::string_literals;

bow::Application::~Application() noexcept {
	::bow::log("app"s, "quitting"s);

	delete this->client;
	delete this->server;

	::fmt::print("\nGoodbye! \u2764\n");
}
