// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/server.hxx>

#include <cstdio>
#include <exception>
#include <fmt/core.h>
#include <format>

auto bow::ServerInstance::run(::bow::ServerInstance* server) noexcept -> void {
	::fmt::print(stderr, "[server] angle unit:             {:.3f} rad\n",               0x1p0);
	::fmt::print(stderr, "[server] distance unit:          {:.3f} m\n",                 ::bow::DISTANCE_MODIFIER);
	::fmt::print(stderr, "[server] mass unit:              {:.3f} kg\n",                ::bow::MASS_MODIFIER);
	::fmt::print(stderr, "[server] time unit:              {:.3f} s\n",                 ::bow::TIME_MODIFIER);
	::fmt::print(stderr, "[server] gravitational constant: {:.9f} (factor: {:.3f}))\n", ::bow::GRAVITY_VALUE, ::bow::GRAVITY_FACTOR);

	if constexpr (!::bow::DEBUG) {
		try {
			server->loop();
		} catch (::std::exception const& exception) {
			::bow::terminate("server", ::std::format("got uncaught exception: {}", exception.what()));
		} catch (...) {
			::bow::terminate("server", "got uncaught exception");
		}
	} else {
		server->loop();
	}
}
