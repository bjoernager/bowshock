// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/application.hxx>

#include <cstdio>
#include <fmt/core.h>

bow::Application::~Application() noexcept {
	::fmt::print(stderr, "[app] quitting\n");

	delete this->client;
	delete this->server;

	::fmt::print(stderr, "\nGoodbye! \u2764\n");
}
