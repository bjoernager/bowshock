// Copyright 2022-2023 Gabriel Jensen.

#include <bow/ini.hxx>

#include <csignal>

::std::sig_atomic_t volatile ::bow::gotint;

namespace bow {
	static auto inthnd(int const sig) -> void;
}

static auto ::bow::inthnd(int const sig) -> void {
	::std::signal(sig,::bow::inthnd); // Ignore the return value: We can't do anything (meaningful) about it anyways.
	::bow::gotint = 0x1;
};

auto ::bow::bow::inisig() noexcept -> void {
	bow_log("initialising signal handlers");

	::bow::gotint = 0x0;

	auto const sethnd = []<typename hndtyp>(int const sig,hndtyp const & hnd) -> void {
		if (::std::signal(sig,static_cast<auto (*)(int) -> void>(hnd)) == SIG_ERR) [[unlikely]] {
			bow_log("unable to set signal handler for %i",sig);
			::bow::abr();
		}
	};

	sethnd(SIGINT, ::bow::inthnd);
	sethnd(SIGTERM,::bow::inthnd);
}
