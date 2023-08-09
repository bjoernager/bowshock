// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/server.hxx>

#include <atomic>

::bow::ServerInstance::ServerInstance(::bow::ServerConfiguration const& configuration, ::std::atomic_flag* stop_flag) noexcept {
	this->configuration = configuration;

	this->stop_flag = stop_flag;
}
