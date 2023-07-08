// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#pragma once

#include <bow/base.hxx>

#include <cstdint>

namespace bow {
	constexpr double DISTANCE_MODIFIER = 0x1.16A5D2D360000000p037; // 1 astronomical unit
	constexpr double MASS_MODIFIER = 0x1.91930A5E75F0C192p100; // 1 solar mass
	constexpr double TIME_MODIFIER = 0x1.0000000000000000p012; // 1 second

	constexpr double GRAVITY_FACTOR = (::bow::MASS_MODIFIER * (::bow::TIME_MODIFIER * ::bow::TIME_MODIFIER)) / ((::bow::DISTANCE_MODIFIER * ::bow::DISTANCE_MODIFIER * ::bow::DISTANCE_MODIFIER)); // Inverse.

	constexpr double GRAVITY_VALUE = 0x1.258688101B4BB16Dp-34 * ::bow::GRAVITY_FACTOR; // gravitational constant (s^2*m*t^2)

	[[nodiscard]] auto ship_mass(::bow::Ship identifier) noexcept -> double;

	auto gravitate(::bow::ObjectRoot& system)                                   noexcept -> void;
	auto gravitate(::bow::ObjectRoot& objects, ::bow::ObjectRoot const& system) noexcept -> void;

	auto move(::bow::ObjectRoot& root) noexcept -> void;

	auto simulate(::bow::ObjectRoot& system, ::std::uint64_t duration) noexcept -> void;
}
