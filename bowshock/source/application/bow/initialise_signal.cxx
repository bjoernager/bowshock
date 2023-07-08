// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/application.hxx>

#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <fmt/core.h>

::std::sig_atomic_t volatile ::bow::GOT_INTERRUPT;

namespace bow {
	static auto interrupt_handler(int const signal) -> void;
}

static auto ::bow::interrupt_handler(int const signal) -> void {
	// Ignore the return value: We canister't do anything (meaningful) about it anyways.
	::std::signal(signal, ::bow::interrupt_handler);

	::bow::GOT_INTERRUPT = 0x1;
};

auto ::bow::Application::initialise_signal() noexcept -> void {
	::fmt::print(stderr, "initialising signal handlers\n");

	::bow::GOT_INTERRUPT = 0x0;

	auto const set_handler = []<typename Handler>(int const signal, Handler const& handler) -> void {
		if (::std::signal(signal, static_cast<auto (*)(int) -> void>(handler)) == SIG_ERR) [[unlikely]] {
			::fmt::print(stderr, "unable to set signal handler for {}\n", signal);

			::std::abort();
		}
	};

	set_handler(SIGINT,  ::bow::interrupt_handler);
	set_handler(SIGTERM, ::bow::interrupt_handler);
}
