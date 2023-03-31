// Copyright 2022-2023 Gabriel Jensen.

#include <bow/bs.h>

#include <stdlib.h>
#include <time.h>

void bow_initrnd(void) {
	bow_log("initialising random generator");
	srand((unsigned int)time(nullptr));
}
