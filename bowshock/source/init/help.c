// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.h>

#include <inttypes.h>
#include <stdlib.h>

void bow_help(char const * const progNm) {
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
		bow_verMaj,bow_verMin,bow_verPat,progNm);
		
	exit(EXIT_SUCCESS);
}
