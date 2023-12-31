// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/application.hxx>

#include <atomic>
#include <csignal>
#include <cstdlib>
#include <format>
#include <stdexcept>
#include <string>

using namespace ::std::literals::string_literals;

// 31.10.4.
// constexpr atomic_flag::atomic_flag() noexcept;
// Effects: Initializes *this to the clear state.
::std::atomic_flag bow::GOT_INTERRUPT;

namespace bow {
	static auto interrupt_handler(int const signal) -> void;
}

static auto bow::interrupt_handler(int const signal) -> void {
	// Ignore the return value: We canister't do anything (meaningful) about it anyways.
	::std::signal(signal, ::bow::interrupt_handler);

	::bow::GOT_INTERRUPT.test_and_set();
};

auto bow::Application::initialise_signal() -> void {
	::bow::log("app"s, "initialising signal handlers"s);

	auto const set_handler = []<typename Handler>(int const signal, Handler const& handler) -> void {
		if (::std::signal(signal, static_cast<auto (*)(int) -> void>(handler)) == SIG_ERR) [[unlikely]] {
			throw ::std::runtime_error(::std::format("unable to set signal handler for {}", signal));
		}
	};

	set_handler(SIGINT,  ::bow::interrupt_handler);
	set_handler(SIGTERM, ::bow::interrupt_handler);
}
