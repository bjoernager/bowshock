// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/server.hxx>
#include <bow/logic.hxx>

#include <cmath>

namespace bow {
	static auto gravitate_single(::bow::Object& object, ::bow::Object const& parent) noexcept -> void {
		// Gravitate a single object to its parent (the
		// force is unilateral).

		// Calculate the distance between the two objects
		// using the Pythagorean theorem:
		// d = sqrt(a^2+b^2+c^2)
		auto const distance_x   = parent.position.x - object.position.x;
		auto const distance_y   = parent.position.y - object.position.y;
		auto const distance_z   = parent.position.z - object.position.z;
		auto const distance     = ::std::sqrt(distance_x * distance_x + distance_y * distance_y + distance_z * distance_z);

		// Calculate the angle between the X and Y
		// dimensions and the X and Z dimensions.
		auto const angle_y      = ::std::atan2(distance_y, distance_x);
		auto const angle_z      = ::std::atan2(distance_z, distance_x);

		// If two objects overlap - that is, they have a
		// absolute spacing of zero, then we discard the
		// accelerations. We use a value as it makes these
		// function branchless.
		auto const no_overlap   = ::std::abs(distance) != 0x0p0;

		// Calculate the acceleration towards the parent
		// object using Newtonian physics:
		// a = (m/(s^2))G
		auto const acceleration = parent.mass / (distance * distance) * ::bow::GRAVITY_VALUE * static_cast<double>(no_overlap);

		// Calculate the gained velocity on the three
		// dimensions using trigonometry:
		// x = cos(theta_y)*a
		// y = sin(theta_y)*a
		// z = sin(theta_z)*a
		auto const velocity_x   = ::std::cos(angle_y) * acceleration;
		auto const velocity_y   = ::std::sin(angle_y) * acceleration;
		auto const velocity_z   = ::std::sin(angle_z) * acceleration;

		// Append the gained velocities to the existing
		// velocities.
		object.positional_velocity.x += velocity_x;
		object.positional_velocity.y += velocity_y;
		object.positional_velocity.z += velocity_z;
	}

	static void gravitate_pair(::bow::Object& object0, ::bow::Object& object1) noexcept {
		// Gravitate a pair of objects to each other (the
		// force is mutual). Cf. gravitate_single.

		auto const distance_x     = object1.position.x - object0.position.x;
		auto const distance_y     = object1.position.y - object0.position.y;
		auto const distance_z     = object1.position.z - object0.position.z;
		auto const distance       = ::std::sqrt(distance_x * distance_x + distance_y * distance_y + distance_z * distance_z);

		auto const angle_y        = ::std::atan2(distance_y, distance_x);
		auto const angle_z        = ::std::atan2(distance_z, distance_x);

		auto const no_overlap     = ::std::abs(distance) != 0x0p0;

		auto       acceleration0  = ::bow::GRAVITY_VALUE / (distance * distance);
		auto const acceleration1  = acceleration0 * object0.mass * static_cast<double>(no_overlap); // This is negative.
		           acceleration0 *= object1.mass * static_cast<double>(no_overlap);

		auto       velocity_x0    = ::std::cos(angle_y);
		auto       velocity_y0    = ::std::sin(angle_y);
		auto       velocity_z0    = ::std::sin(angle_z);
		auto const velocity_x1    = velocity_x0 * acceleration1;
		auto const velocity_y1    = velocity_y0 * acceleration1;
		auto const velocity_z1    = velocity_z0 * acceleration1;
		           velocity_x0   *= acceleration0;
		           velocity_y0   *= acceleration0;
		           velocity_z0   *= acceleration0;

		object0.positional_velocity.x += velocity_x0;
		object0.positional_velocity.y += velocity_y0;
		object0.positional_velocity.z += velocity_z0;

		object1.positional_velocity.x -= velocity_x1;
		object1.positional_velocity.y -= velocity_y1;
		object1.positional_velocity.z -= velocity_z1;
	}
}

auto bow::ServerInstance::gravitate(::bow::ObjectRoot& system) noexcept -> void {
	for (auto& object0: system) {
		for (auto& object1: system) {
			::bow::gravitate_pair(object0, object1);
		}
	}
}

auto bow::ServerInstance::gravitate(::bow::ObjectRoot& objects, ::bow::ObjectRoot const& system) noexcept -> void {
	for (auto& object0: objects) {
		for (auto const& object1: system) {
			::bow::gravitate_single(object0, object1);
		}
	}
}
