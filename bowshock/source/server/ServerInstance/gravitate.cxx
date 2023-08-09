// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/server.hxx>
#include <bow/logic.hxx>

#include <cmath>

namespace bow {
	static auto gravitate_single(::bow::Object& object, ::bow::Object const& par) noexcept -> void {
		auto const distance_x   = par.position.x - object.position.x;
		auto const distance_y   = par.position.y - object.position.y;
		auto const distance_z   = par.position.z - object.position.z;
		auto const distance     = ::std::sqrt(distance_x * distance_x + distance_y * distance_y + distance_z * distance_z);

		auto const angle_y      = ::std::atan2(distance_y, distance_x);
		auto const angle_z      = ::std::atan2(distance_z, distance_x);

		// If two objects overlap - that is, they have a
		// absolute spacing of zero, then we discard the
		// accelerations. We use a value as it makes these
		// function branchless.
		auto const no_overlap   = ::std::abs(distance) != 0x0p0;

		auto const acceleration = par.mass/(distance * distance) * ::bow::GRAVITY_VALUE * static_cast<double>(no_overlap);

		auto const velocity_x   = ::std::cos(angle_y) * acceleration;
		auto const velocity_y   = ::std::sin(angle_y) * acceleration;
		auto const velocity_z   = ::std::sin(angle_z) * acceleration;

		object.positional_velocity.x += velocity_x;
		object.positional_velocity.y += velocity_y;
		object.positional_velocity.z += velocity_z;
	}

	static void gravitate_pair(::bow::Object& obj0, ::bow::Object& obj1) noexcept {
		auto const distance_x     = obj1.position.x - obj0.position.x;
		auto const distance_y     = obj1.position.y - obj0.position.y;
		auto const distance_z     = obj1.position.z - obj0.position.z;
		auto const distance       = ::std::sqrt(distance_x * distance_x + distance_y * distance_y + distance_z * distance_z);

		auto const angle_y        = ::std::atan2(distance_y, distance_x);
		auto const angle_z        = ::std::atan2(distance_z, distance_x);

		auto const no_overlap     = ::std::abs(distance) != 0x0p0;

		auto       acceleration0  = ::bow::GRAVITY_VALUE / (distance * distance);
		auto const acceleration1  = acceleration0 * obj0.mass * static_cast<double>(no_overlap); // This is negative.
		           acceleration0 *= obj1.mass * static_cast<double>(no_overlap);

		auto       velocity_x0    = ::std::cos(angle_y);
		auto       velocity_y0    = ::std::sin(angle_y);
		auto       velocity_z0    = ::std::sin(angle_z);
		auto const velocity_x1    = velocity_x0 * acceleration1;
		auto const velocity_y1    = velocity_y0 * acceleration1;
		auto const velocity_z1    = velocity_z0 * acceleration1;
		           velocity_x0   *= acceleration0;
		           velocity_y0   *= acceleration0;
		           velocity_z0   *= acceleration0;

		obj0.positional_velocity.x += velocity_x0;
		obj0.positional_velocity.y += velocity_y0;
		obj0.positional_velocity.z += velocity_z0;

		obj1.positional_velocity.x -= velocity_x1;
		obj1.positional_velocity.y -= velocity_y1;
		obj1.positional_velocity.z -= velocity_z1;
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
