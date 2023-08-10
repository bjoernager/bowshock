// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/logic.hxx>
#include <bow/server.hxx>

#include <atomic>
#include <thread>
#include <utility>

using namespace ::std::literals::string_literals;

auto bow::Server::start(::bow::ServerConfiguration const& configuration) -> ::bow::Server* {
	::bow::log("app"s, "starting server"s);

	auto stop_flag = new ::std::atomic_flag();

	auto server = new ::bow::ServerInstance(configuration, stop_flag);

	auto thread = new ::std::thread(::bow::ServerInstance::run, server);

	auto const instance = new ::bow::Server;

	instance->thread    = ::std::move(thread);
	instance->instance  = ::std::move(server);
	instance->stop_flag = ::std::move(stop_flag);

	return instance;
}
