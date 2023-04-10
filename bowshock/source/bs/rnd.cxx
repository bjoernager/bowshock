// Copyright 2022-2023 Gabriel Jensen.

#include <bow/bs.hxx>

#include <cstdlib>

static_assert(sizeof (int) == sizeof (::zap::i02));

static_assert(RAND_MAX == ::zap::maxval<int>);

unsigned long ::bow::rnd() noexcept {
	::zap::i02 const rnd0 = (::zap::i02)::std::rand();
	::zap::i02 const rnd1 = (::zap::i02)::std::rand();
	::zap::i04 const rnd = (::zap::i04)rnd0 | (::zap::i04)rnd1 >> 0x4u;
	
	return rnd;
}
