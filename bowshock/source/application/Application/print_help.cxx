// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/application.hxx>

#include <cstdlib>
#include <fmt/core.h>

auto bow::Application::print_help(::std::string const& program_name) noexcept -> void {
	::fmt::print(
		"\n"
		"\x1B[1mBowshock\x1B[0m {:X}.{:X}.{:X}\n"
		"Copyright \u00A9 2022\u20102023 \x1B[1mGabriel Bj\u00F8rnager Jensen\x1B[0m.\n"
		"\n"
		"Usage: \"{}\" <parameters> <flags>\n"
		"\n"
		"Parameters:\n"
		"    directory Set the application \x1B[1mdirectory\x1B[0m to be used\n"
		"    port      Set the (decimal) \x1B[1mport\x1B[0m number used to connect to the server\n"
		"    save      Set the \x1B[1mname\x1B[0m of the save file\n"
		"\n"
		"Flags:\n"
		"    credits Print the game \x1B[1mcredits\x1B[0m\n"
		"    help    Print the \x1B[1mhelp\x1B[0m screen\n"
		"    new     Start a \x1B[1mnew\x1B[0m save file\n"
		"    skip    \x1B[1mskip\x1B[0m the intro\n"
		"\n",
		::bow::VERSION.major, ::bow::VERSION.minor, ::bow::VERSION.patch, program_name
	);

	::std::exit(EXIT_SUCCESS);
}
