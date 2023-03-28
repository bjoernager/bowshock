// Copyright 2022-2023 Gabriel Jensen.

#include <bow/lgc.h>

#include <math.h>
#include <zap/mem.h>

void bow_grav1(bow_obj * objptr,bow_obj * parptr) {
	bow_obj obj;
	bow_obj par;
	zap_cp(&obj,objptr,sizeof (obj));
	zap_cp(&par,parptr,sizeof (par));
	double const distx = par.pos.x-obj.pos.x;
	double const disty = par.pos.y-obj.pos.y;
	double const distz = par.pos.z-obj.pos.z;
	double const dist  = sqrt(distx*distx+disty*disty+distz*distz);
	double const angy  = atan2(disty,distx);
	double const angz  = atan2(distz,distx);
	double       acc   = par.mass/pow(dist,2.0)*bow_gravconst;
	double const vx    = cos(angy)*acc;
	double const vy    = sin(angy)*acc;
	double const vz    = sin(angz)*acc;
	obj.posvel.x += vx;
	obj.posvel.y += vy;
	obj.posvel.z += vz;
	zap_cp(objptr,&obj,sizeof (obj));
}

void bow_grav2(bow_obj * obj0ptr,bow_obj * obj1ptr) {
	bow_obj obj0;
	bow_obj obj1;
	zap_cp(&obj0,obj0ptr,sizeof (obj0));
	zap_cp(&obj1,obj1ptr,sizeof (obj1));
	double const distx  = obj1.pos.x-obj0.pos.x;
	double const disty  = obj1.pos.y-obj0.pos.y;
	double const distz  = obj1.pos.z-obj0.pos.z;
	double const dist   = sqrt(distx*distx+disty*disty+distz*distz);
	double const angy   = atan2(disty,distx);
	double const angz   = atan2(distz,distx);
	double       acc0   = bow_gravconst/pow(dist,2.0);
	double const acc1   = acc0*obj0.mass; // This is negative.
	             acc0  *= obj1.mass;
	double       vx0    = cos(angy);
	double       vy0    = sin(angy);
	double       vz0    = sin(angz);
	double const vx1    = vx0*acc1;
	double const vy1    = vy0*acc1;
	double const vz1    = vz0*acc1;
	             vx0   *= acc0;
	             vy0   *= acc0;
	             vz0   *= acc0;
	obj0.posvel.x += vx0;
	obj0.posvel.y += vy0;
	obj0.posvel.z += vz0;
	obj1.posvel.x -= vx1;
	obj1.posvel.y -= vy1;
	obj1.posvel.z -= vz1;
	zap_cp(obj0ptr,&obj0,sizeof (obj0));
	zap_cp(obj1ptr,&obj1,sizeof (obj1));
}

void bow_gravsys(bow_objroot const * const sys) {
	for (bow_obj * obj0 = sys->objs;obj0 != nullptr;obj0 = obj0->next) 
		for (bow_obj * obj1 = obj0->next;obj1 != nullptr;obj1 = obj1->next)
			bow_grav2(obj0,obj1);
}

void bow_gravobjs(bow_objroot const * const sys,bow_objroot const * const objs) {
	for (bow_obj * obj = objs->objs;obj != nullptr;obj = obj->next) 
		for (bow_obj * par = sys->objs;par != nullptr;par = par->next)
			bow_grav1(obj,par);
}
