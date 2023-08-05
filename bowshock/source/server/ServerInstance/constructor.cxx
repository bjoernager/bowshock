// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/server.hxx>

#include <atomic>

::bow::ServerInstance::ServerInstance(::std::atomic_flag* stop_flag) noexcept {
	this->stop_flag = stop_flag;
}
