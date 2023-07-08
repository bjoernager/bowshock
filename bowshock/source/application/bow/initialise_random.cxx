// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/application.hxx>

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fmt/core.h>

auto ::bow::Application::initialise_random() noexcept -> void {
	::fmt::print(stderr, "initialising random number generator\n");

	::std::srand(static_cast<unsigned int>(::std::time(nullptr)));
}
