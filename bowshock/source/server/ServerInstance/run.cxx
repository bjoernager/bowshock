// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/server.hxx>

#include <exception>
#include <format>
#include <string>

using namespace ::std::literals::string_literals;

auto bow::ServerInstance::run(::bow::ServerInstance* server) noexcept -> void {
	::bow::log("server"s, ::std::format("angle unit:             {:.3f} rad",                0x1p0));
	::bow::log("server"s, ::std::format("distance unit:          {:.3f} m",                  ::bow::DISTANCE_MODIFIER));
	::bow::log("server"s, ::std::format("mass unit:              {:.3f} kg",                 ::bow::MASS_MODIFIER));
	::bow::log("server"s, ::std::format("time unit:              {:.3f} s",                  ::bow::TIME_MODIFIER));
	::bow::log("server"s, ::std::format("gravitational constant: {:.9f} (factor: {:.3f}s))", ::bow::GRAVITY_VALUE, ::bow::GRAVITY_FACTOR));

	if constexpr (!::bow::DEBUG) {
		try {
			server->loop();
		} catch (::std::exception const& exception) {
			::bow::terminate("server"s, ::std::format("got uncaught exception: {}", exception.what()));
		} catch (...) {
			::bow::terminate("server"s, "got uncaught exception"s);
		}
	} else {
		server->loop();
	}
}
