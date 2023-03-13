#define bow_sym "quit"

#include <bow/info.h>

#include <flux.h>
#include <stdio.h>
#include <stdlib.h>

void bow_quit(bow_stat const stat) {
	bow_log("goodbye");
	int sysstat;
	switch (stat) {
	case bow_stat_err:
		sysstat = EXIT_FAILURE;
		break;
	case bow_stat_ok:
		sysstat = EXIT_SUCCESS;
		break;
	}
	bow_log("exiting with code %i",sysstat);
	exit(sysstat);
}
