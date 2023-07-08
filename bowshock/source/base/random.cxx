// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/base.hxx>

#include <cstdint>
#include <cstdlib>
#include <limits>

static_assert(sizeof (int) == sizeof (::std::uint32_t));

static_assert(RAND_MAX == ::std::numeric_limits<int>::max());

auto ::bow::random() noexcept -> ::std::uint64_t {
	::std::uint32_t const rnd0 = (::std::uint32_t)::std::rand();
	::std::uint32_t const rnd1 = (::std::uint32_t)::std::rand();
	::std::uint64_t const random  = static_cast<::std::uint64_t>(rnd0) | static_cast<::std::uint64_t>(rnd1) >> 0x4u;

	return random;
}
