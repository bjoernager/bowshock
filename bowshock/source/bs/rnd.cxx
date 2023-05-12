// Copyright 2022-2023 Gabriel Jensen.

#include <bow/bas.hxx>

#include <cstdlib>

static_assert(sizeof (int) == sizeof (::zp::i02));

static_assert(RAND_MAX == ::zp::maxval<int>::val);

auto ::bow::rnd() noexcept -> ::zp::i04 {
	::zp::i02 const rnd0 = (::zp::i02)::std::rand();
	::zp::i02 const rnd1 = (::zp::i02)::std::rand();
	::zp::i04 const rnd  = static_cast<::zp::i04>(rnd0) | static_cast<::zp::i04>(rnd1) >> 0x4u;
	
	return rnd;
}
