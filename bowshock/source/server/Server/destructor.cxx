// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/server.hxx>

using namespace ::std::literals::string_literals;

::bow::Server::~Server() noexcept {
	::bow::log("app"s, "stopping server"s);

	this->stop_flag->test_and_set();

	// Wait for the server to submit.
	this->thread->join();

	delete this->stop_flag;

	delete this->instance;

	delete this->thread;
}
