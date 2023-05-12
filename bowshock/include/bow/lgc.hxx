// Copyright 2022-2023 Gabriel Jensen.

#pragma once

#include <bow/bas.hxx>

namespace bow {
	constexpr ::zp::f04 dstmod = 0x1.16A5D2D360000000p037; // distance modifier (1 astronomical unit)
	constexpr ::zp::f04 masmod = 0x1.91930A5E75F0C192p100; // mass modifier     (1 solar mas)
	constexpr ::zp::f04 timmod = 0x1.0000000000000000p012; // time modifier     (1 second)

	constexpr ::zp::f04 grvfac = (::bow::masmod*(::bow::timmod*::bow::timmod))/((::bow::dstmod*::bow::dstmod*::bow::dstmod)); // inverse

	constexpr ::zp::f04 grvval = 0x1.258688101B4BB16Dp-34*::bow::grvfac; // gravitational constant (s^2*m*t^2)

	[[nodiscard]] auto shpmas(::bow::shp id) noexcept -> ::zp::f04;

	auto grv(::bow::objroot & sys)                             noexcept -> void;
	auto grv(::bow::objroot & objs,::bow::objroot const & sys) noexcept -> void;
	auto mov(::bow::objroot & root)                            noexcept -> void;

	auto sim(::bow::objroot & sys,::zp::i04 dur) noexcept -> void;
}
