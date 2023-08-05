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

		auto const acceleration = par.mass/(distance*distance)*::bow::GRAVITY_VALUE;

		auto const velocity_x   = ::std::cos(angle_y)*acceleration;
		auto const velocity_y   = ::std::sin(angle_y)*acceleration;
		auto const velocity_z   = ::std::sin(angle_z)*acceleration;

		object.positional_velocity.x += velocity_x;
		object.positional_velocity.y += velocity_y;
		object.positional_velocity.z += velocity_z;
	}

	static void gravitate_pair(::bow::Object& obj0, ::bow::Object& obj1) noexcept {
		auto const distance_x     = obj1.position.x-obj0.position.x;
		auto const distance_y     = obj1.position.y-obj0.position.y;
		auto const distance_z     = obj1.position.z-obj0.position.z;
		auto const distance       = ::std::sqrt(distance_x*distance_x+distance_y*distance_y+distance_z*distance_z);

		auto const angle_y        = ::std::atan2(distance_y, distance_x);
		auto const angle_z        = ::std::atan2(distance_z, distance_x);

		auto       acceleration0  = ::bow::GRAVITY_VALUE/(distance*distance);
		auto const acceleration1  = acceleration0*obj0.mass; // This is negative.
		           acceleration0 *= obj1.mass;

		auto       velocity_x0    = ::std::cos(angle_y);
		auto       velocity_y0    = ::std::sin(angle_y);
		auto       velocity_z0    = ::std::sin(angle_z);
		auto const velocity_x1    = velocity_x0*acceleration1;
		auto const velocity_y1    = velocity_y0*acceleration1;
		auto const velocity_z1    = velocity_z0*acceleration1;
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
	for (::bow::Object* obj0 = system.objects; obj0 != nullptr; obj0 = obj0->next) {
		for (::bow::Object* obj1 = obj0->next; obj1 != nullptr; obj1 = obj1->next) {
			::bow::gravitate_pair(*obj0, *obj1);
		}
	}
}

auto bow::ServerInstance::gravitate(::bow::ObjectRoot& objects, ::bow::ObjectRoot const& system) noexcept -> void {
	for (::bow::Object* object = objects.objects; object != nullptr; object = object->next) {
		for (::bow::Object* par = system.objects; par != nullptr; par = par->next) {
			::bow::gravitate_single(*object, *par);
		}
	}
}
