// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.h>

#include <stdlib.h>
#include <time.h>

void bow_initRnd(void) {
	bow_log("initialising random number generator");
	
	srand((unsigned int)time(nullptr));
}
