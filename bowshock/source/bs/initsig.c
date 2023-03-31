// Copyright 2022-2023 Gabriel Jensen.

#include <bow/bs.h>

#include <signal.h>

sig_atomic_t volatile bow_gotintr;

static void bow_intrhandl(int const sig) {
	signal(sig,bow_intrhandl); // Ignore the return value.
	bow_gotintr = 0x1;
}

void bow_initsig(void) {
	bow_log("initialising signal handlers");
	bow_gotintr = 0x0;
	if (signal(SIGINT,bow_intrhandl) == SIG_ERR) {
		bow_log("unable to set signal handler");
		bow_abrt();
	}
}
