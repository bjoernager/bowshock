// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/application.hxx>
#include <bow/logic.hxx>
#include <bow/runtime.hxx>
#include <bow/save.hxx>

#include <cstdio>
#include <fmt/core.h>

auto ::bow::Application::run(int const argc, char const* const* const argv) noexcept -> void {
	::bow::TerminalOptions options;
	check_parameters(options, argc, argv);

	print_quote();

	::fmt::print(
		stderr,
		"\x1B[0m\x1B[1mBowshock\x1B[0m {:X}.{:X}.{:X} \u2013 Copyright 2022\u20102023 \x1B[1mGabriel Bj\u00F8rnager Jensen\x1B[0m.\n\n",
		::bow::VERSION.major, ::bow::VERSION.minor, ::bow::VERSION.patch
	);

	::fmt::print(stderr, "initialising\n");

	if constexpr (::bow::DEBUG) { ::fmt::print(stderr, "debug mode is enabled\n"); }

	::fmt::print(stderr, "data directory at \"{}\"\n", ::bow::DATA_DIRECTORY);

	::fmt::print(stderr, "angle unit:             {:.3f} radians\n",           0x1p0);
	::fmt::print(stderr, "distance unit:          {:.3f} metres\n",            ::bow::DISTANCE_MODIFIER);
	::fmt::print(stderr, "mass unit:              {:.3f} kilograms\n",         ::bow::MASS_MODIFIER);
	::fmt::print(stderr, "time unit:              {:.3f} seconds\n",           ::bow::TIME_MODIFIER);
	::fmt::print(stderr, "gravitational constant: {:.3f} (factor: {:.3f}))\n", ::bow::GRAVITY_VALUE, ::bow::GRAVITY_FACTOR);

	this->initialise_random();
	this->initialise_signal();
	this->initialise_graphics();

	if (options.skip_intro || !start_sequence()) [[likely]] {
		if (!options.has_save_path) { options.save_path = ::bow::save_path(); }

		if (options.new_save) { ::bow::new_save(player_data); }
		else                  { ::bow::continue_save(player_data, options.save_path); }

		this->loop();

		::bow::save(options.save_path, player_data);
	}
}

int main(int const argc, char const* const* argv) {
	::bow::Application bow;

	bow.run(argc, argv);
}
