// Copyright 2022-2023 Gabriel Jensen.

#include <bow/bs.hxx>

#include <cstdlib>

static_assert(sizeof (int) == sizeof (::zp::i02));

static_assert(RAND_MAX == ::zp::maxval<int>::val);

unsigned long ::bow::rnd() noexcept {
	::zp::i02 const rnd0 = (::zp::i02)::std::rand();
	::zp::i02 const rnd1 = (::zp::i02)::std::rand();
	::zp::i04 const rnd = (::zp::i04)rnd0 | (::zp::i04)rnd1 >> 0x4u;
	
	return rnd;
}
