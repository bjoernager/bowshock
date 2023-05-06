// Copyright 2022-2023 Gabriel Jensen.

#pragma once

#include <bow/bs.hxx>

namespace bow {
	constexpr double distMod = 0x1.16A5D2D360000000p037; // distance modifier (1 astronomical unit)
	constexpr double massMod = 0x1.91930A5E75F0C192p100; // mass modifier     (1 solar mass)
	constexpr double tmMod   = 0x1.0000000000000000p012; // time modifier     (1 second)

	constexpr double gravConstFac = (::bow::massMod*(::bow::tmMod*::bow::tmMod))/((::bow::distMod*::bow::distMod*::bow::distMod)); // inverse

	constexpr double gravConst = 0x1.258688101B4BB16Dp-34*::bow::gravConstFac; // gravitational constant (s^2*m*t^2)

	zp_useq double shipMass(::bow::ship id) noexcept;

	void grav(::bow::objRoot & sys)                             noexcept;
	void grav(::bow::objRoot & objs,::bow::objRoot const & sys) noexcept;
	void mv(  ::bow::objRoot & root)                            noexcept;

	void sim(::bow::objRoot & sys,::zp::i04 dur) noexcept;
}
