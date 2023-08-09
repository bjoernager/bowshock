// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/logic.hxx>
#include <bow/server.hxx>

#include <atomic>
#include <cstdio>
#include <fmt/core.h>
#include <thread>
#include <utility>

auto bow::Server::start(::bow::ServerConfiguration const& configuration) -> ::bow::Server* {
	::fmt::print(stderr, "[app] starting server\n");

	auto stop_flag = new ::std::atomic_flag();

	auto server = new ::bow::ServerInstance(configuration, stop_flag);

	auto thread = new ::std::thread(::bow::ServerInstance::run, server);

	auto const instance = new ::bow::Server;

	instance->thread    = ::std::move(thread);
	instance->instance  = ::std::move(server);
	instance->stop_flag = ::std::move(stop_flag);

	return instance;
}
