// Copyright 2022-2023 Gabriel Jensen.

#include <bow/ini.hxx>

#include <csignal>

::std::sig_atomic_t volatile ::bow::gotint;

namespace bow {
	static auto intHnd(int const sig) -> void {
		::std::signal(sig,::bow::intHnd); // Ignore the return value: We can't do anything (meaningful) about it anyways.
		::bow::gotint = 0x1;
	}
}

auto ::bow::bow::inisig() noexcept -> void {
	bow_log("initialising signal handlers");

	::bow::gotint = 0x0;
	
	if (::std::signal(SIGINT,::bow::intHnd) == SIG_ERR) [[unlikely]] {
		bow_log("unable to set signal handler");
		::bow::abr();
	}
}
