// Copyright 2022-2023 Gabriel Jensen.

#include <bow/lgc.hxx>

#include <cmath>

namespace bow {
	static void grav1(::bow::obj & obj,::bow::obj const & par) noexcept {
		double const distx = par.pos.x-obj.pos.x;
		double const disty = par.pos.y-obj.pos.y;
		double const distz = par.pos.z-obj.pos.z;
		double const dist  = ::std::sqrt(distx*distx+disty*disty+distz*distz);

		double const angy  = ::std::atan2(disty,distx);
		double const angz  = ::std::atan2(distz,distx);

		double       acc   = par.mass/(dist*dist)*::bow::gravConst;

		double const vx    = ::std::cos(angy)*acc;
		double const vy    = ::std::sin(angy)*acc;
		double const vz    = ::std::sin(angz)*acc;

		obj.posVel.x += vx;
		obj.posVel.y += vy;
		obj.posVel.z += vz;
	}

	static void grav2(::bow::obj & obj0,::bow::obj & obj1) noexcept {
		double const distx  = obj1.pos.x-obj0.pos.x;
		double const disty  = obj1.pos.y-obj0.pos.y;
		double const distz  = obj1.pos.z-obj0.pos.z;
		double const dist   = ::std::sqrt(distx*distx+disty*disty+distz*distz);

		double const angy   = ::std::atan2(disty,distx);
		double const angz   = ::std::atan2(distz,distx);

		double       acc0   = ::bow::gravConst/(dist*dist);
		double const acc1   = acc0*obj0.mass; // This is negative.
		             acc0  *= obj1.mass;

		double       vx0    = ::std::cos(angy);
		double       vy0    = ::std::sin(angy);
		double       vz0    = ::std::sin(angz);
		double const vx1    = vx0*acc1;
		double const vy1    = vy0*acc1;
		double const vz1    = vz0*acc1;
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
	
void ::bow::grav(::bow::objRoot & sys) noexcept {
	for (::bow::obj * obj0 = sys.objs;obj0 != nullptr;obj0 = obj0->next) {
		for (::bow::obj * obj1 = obj0->next;obj1 != nullptr;obj1 = obj1->next) {
			::bow::grav2(*obj0,*obj1);
		}
	}
}

void ::bow::grav(::bow::objRoot & objs,::bow::objRoot const & sys) noexcept {
	for (::bow::obj * obj = objs.objs;obj != nullptr;obj = obj->next) {
		for (::bow::obj * par = sys.objs;par != nullptr;par = par->next) {
			::bow::grav1(*obj,*par);
		}
	}
}
