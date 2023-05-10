// Copyright 2022-2023 Gabriel Jensen.

#include <bow/ini.hxx>

#include <cinttypes>
#include <cstdlib>

auto ::bow::bow::hlp(char const * const progNm) noexcept -> void {
	bow_lograw(
		"\n"
		"\x1B[1mBowshock\x1B[0m %" PRIX64 ".%" PRIX64 ".%" PRIX64 "\n"
		"Copyright 2022-2023 Gabriel Jensen.\n"
		"\n"
		"Usage: \"%s\" <options> [savefile]\n"
		"\n"
		"Options:\n"
		"    --credits    Print the game \x1B[1mcredits\x1B[0m\n"
		"    --help       Print \x1B[1mhelp\x1B[0m screen\n"
		"    --new        srt a \x1B[1mnew\x1B[0m save file\n"
		"    --skip       \x1B[1mSkip\x1B[0m the intro\n"
		"\n",
		::bow::vermaj,::bow::vermin,::bow::verpat,progNm);
		
	::std::exit(EXIT_SUCCESS);
}
