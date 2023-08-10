// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/client.hxx>
#include <bow/logic.hxx>

#include <cmath>
#include <exception>
#include <format>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

using namespace ::std::literals::string_literals;

auto bow::Client::run() noexcept -> void {
	::bow::log("client"s, "running"s);

	if (!this->configuration.skip_start_sequence) [[likely]] {
		auto stop = false;

		if constexpr (!::bow::DEBUG) {
			try {
				stop = this->start_sequence();
			} catch (::std::exception const& exception) {
				::bow::terminate("client"s, ::std::format("got uncaught exception: {}", exception.what()));
			}
		} else {
			stop = this->start_sequence();
		}

		if (stop) [[unlikely]] { return; }
	}

	if constexpr (!::bow::DEBUG) {
		try {
			this->loop();
		} catch (::std::exception const& exception) {
			::bow::terminate("client"s, ::std::format("got uncaught exception: {}", exception.what()));
		}
	} else {
		this->loop();
	}
}
