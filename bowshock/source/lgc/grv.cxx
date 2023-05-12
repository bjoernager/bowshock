// Copyright 2022-2023 Gabriel Jensen.

#include <bow/lgc.hxx>

#include <cmath>

namespace bow {
	static auto grav1(::bow::obj & obj,::bow::obj const & par) noexcept -> void {
		::zp::f04 const distx = par.pos.x-obj.pos.x;
		::zp::f04 const disty = par.pos.y-obj.pos.y;
		::zp::f04 const distz = par.pos.z-obj.pos.z;
		::zp::f04 const dist  = ::std::sqrt(distx*distx+disty*disty+distz*distz);

		::zp::f04 const angy  = ::std::atan2(disty,distx);
		::zp::f04 const angz  = ::std::atan2(distz,distx);

		::zp::f04     acc   = par.mas/(dist*dist)*::bow::grvval;

		::zp::f04 const vx    = ::std::cos(angy)*acc;
		::zp::f04 const vy    = ::std::sin(angy)*acc;
		::zp::f04 const vz    = ::std::sin(angz)*acc;

		obj.posVel.x += vx;
		obj.posVel.y += vy;
		obj.posVel.z += vz;
	}

	static void grav2(::bow::obj & obj0,::bow::obj & obj1) noexcept {
		::zp::f04 const distx  = obj1.pos.x-obj0.pos.x;
		::zp::f04 const disty  = obj1.pos.y-obj0.pos.y;
		::zp::f04 const distz  = obj1.pos.z-obj0.pos.z;
		::zp::f04 const dist   = ::std::sqrt(distx*distx+disty*disty+distz*distz);

		::zp::f04 const angy   = ::std::atan2(disty,distx);
		::zp::f04 const angz   = ::std::atan2(distz,distx);

		::zp::f04     acc0   = ::bow::grvval/(dist*dist);
		::zp::f04 const acc1   = acc0*obj0.mas; // This is negative.
		             acc0  *= obj1.mas;

		::zp::f04     vx0    = ::std::cos(angy);
		::zp::f04     vy0    = ::std::sin(angy);
		::zp::f04     vz0    = ::std::sin(angz);
		::zp::f04 const vx1    = vx0*acc1;
		::zp::f04 const vy1    = vy0*acc1;
		::zp::f04 const vz1    = vz0*acc1;
		             vx0   *= acc0;
		             vy0   *= acc0;
		             vz0   *= acc0;

		obj0.posVel.x += vx0;
		obj0.posVel.y += vy0;
		obj0.posVel.z += vz0;

		obj1.posVel.x -= vx1;
		obj1.posVel.y -= vy1;
		obj1.posVel.z -= vz1;
	}
}
	
auto ::bow::grv(::bow::objroot & sys) noexcept -> void {
	for (::bow::obj * obj0 = sys.objs;obj0 != nullptr;obj0 = obj0->nxt) {
		for (::bow::obj * obj1 = obj0->nxt;obj1 != nullptr;obj1 = obj1->nxt) {
			::bow::grav2(*obj0,*obj1);
		}
	}
}

auto ::bow::grv(::bow::objroot & objs,::bow::objroot const & sys) noexcept -> void {
	for (::bow::obj * obj = objs.objs;obj != nullptr;obj = obj->nxt) {
		for (::bow::obj * par = sys.objs;par != nullptr;par = par->nxt) {
			::bow::grav1(*obj,*par);
		}
	}
}
