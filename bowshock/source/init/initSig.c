// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.h>

#include <signal.h>

sig_atomic_t volatile bow_gotIntr;

static void bow_intrHand(int const sig) {
	signal(sig,bow_intrHand); // Ignore the return value: We can't do anything (meaningful) about it anyways.
	bow_gotIntr = 0x1;
}

void bow_initSig(void) {
	bow_log("initialising signal handlers");

	bow_gotIntr = 0x0;
	
	unlikely (signal(SIGINT,bow_intrHand) == SIG_ERR) {
		bow_log("unable to set signal handler");
		bow_abrt();
	}
}
