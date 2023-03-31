// Copyright 2022-2023 Gabriel Jensen.

#include <bow/bs.h>

#include <stdlib.h>
#include <zap/bs.h>

static_assert(sizeof (int) == sizeof (zap_i02));

static_assert(RAND_MAX == zap_maxvali);

zap_i04 bow_rnd(void) {
	zap_i02 const rnd0 = (zap_i02)rand();
	zap_i02 const rnd1 = (zap_i02)rand();
	zap_i04 const rnd = (zap_i04)rnd0 | (zap_i04)rnd1 >> 0x4u;
	return rnd;
}
