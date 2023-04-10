// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.hxx>

#include <csignal>

::std::sig_atomic_t volatile ::bow::gotIntr;

namespace bow {
	static void intrHand(int const sig) {
		::std::signal(sig,::bow::intrHand); // Ignore the return value: We can't do anything (meaningful) about it anyways.
		::bow::gotIntr = 0x1;
	}
}

void ::bow::bow::initSig() noexcept {
	bow_log("initialising signal handlers");

	::bow::gotIntr = 0x0;
	
	if (::std::signal(SIGINT,::bow::intrHand) == SIG_ERR) [[unlikely]] {
		bow_log("unable to set signal handler");
		::bow::abrt();
	}
}
