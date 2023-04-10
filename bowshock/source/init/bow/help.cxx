// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.hxx>

#include <cinttypes>
#include <cstdlib>

void ::bow::bow::help(char const * const progNm) noexcept {
	bow_logRaw(
		"\n"
		"\x1B[1mBowshock\x1B[0m %" PRIX64 ".%" PRIX64 ".%" PRIX64 "\n"
		"Copyright 2022-2023 Gabriel Jensen.\n"
		"\n"
		"Usage: \"%s\" <options> [savefile]\n"
		"\n"
		"Options:\n"
		"    --credits    Print the game \x1B[1mcredits\x1B[0m\n"
		"    --help       Print \x1B[1mhelp\x1B[0m screen\n"
		"    --new        Start a \x1B[1mnew\x1B[0m save file\n"
		"    --skip       \x1B[1mSkip\x1B[0m the intro\n"
		"\n",
		::bow::verMaj,::bow::verMin,::bow::verPat,progNm);
		
	::std::exit(EXIT_SUCCESS);
}
