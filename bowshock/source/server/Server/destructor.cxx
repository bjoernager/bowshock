// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/server.hxx>

#include <cstdio>
#include <fmt/core.h>

::bow::Server::~Server() noexcept {
	::fmt::print(stderr, "[app] stopping server\n");

	this->stop_flag->test_and_set();

	// Wait for the server to submit.
	this->thread->join();

	delete this->stop_flag;

	delete this->instance;

	delete this->thread;
}
