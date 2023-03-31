// Copyright 2022-2023 Gabriel Jensen.

#include <bow/bs.h>

#include <inttypes.h>
#include <stdlib.h>

void bow_help(char const * const prognm) {
	bow_rawlog(
		"\n"
		"bowshock %" PRIXLEAST64 ".%" PRIXLEAST64 ".%" PRIXLEAST64 "\n"
		"Copyright 2022-2023 Gabriel Jensen.\n"
		"\n"
		"Usage: %s <options> [savefile]\n"
		"\n"
		"Options:\n"
		"    --help       Print help screen\n"
		"    --restart    Generate default commander\n"
		"\n",
		bow_vermaj,bow_vermin,bow_verpat,prognm);
	exit(EXIT_SUCCESS);
}
