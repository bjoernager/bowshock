// Copyright 2022-2023 Gabriel Jensen.

#include <bow/run.h>

#include <stdlib.h>

void bow_abrt(void) {
	bow_log("aborting");
	
	abort();
}
