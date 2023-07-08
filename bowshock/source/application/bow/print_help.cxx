// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/application.hxx>

#include <cstdlib>
#include <fmt/core.h>

auto ::bow::Application::print_help(::std::string const program_name) noexcept -> void {
	::fmt::print(
		"\n"
		"\x1B[1mBowshock\x1B[0m {:X}.{:X}.{:X}\n"
		"Copyright 2022-2023 Gabriel Bj\u00F8rnager Jensen.\n"
		"\n"
		"Usage: \"{}\" <options> [savefile]\n"
		"\n"
		"Options:\n"
		"    --credits    Print the game \x1B[1mcredits\x1B[0m\n"
		"    --print_help Print the\x1B[1mhelp\x1B[0m screen\n"
		"    --new        Start a \x1B[1mnew\x1B[0m save file\n"
		"    --skip_intro \x1B[1mskip\x1B[0m the intro\n"
		"\n",
		::bow::VERSION.major, ::bow::VERSION.minor, ::bow::VERSION.patch, program_name);

	::std::exit(EXIT_SUCCESS);
}
