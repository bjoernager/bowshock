#define bow_sym "grav"

#include <bow/lgc.h>

#include <math.h>
#include <zap/mem.h>

void bow_grav(bow_obj * obj0ptr,bow_obj * obj1ptr) {
	bow_obj obj0;
	bow_obj obj1;
	zap_cp(&obj0,obj0ptr,sizeof (obj0));
	zap_cp(&obj1,obj1ptr,sizeof (obj1));
	double const distx  = obj1.pos.x-obj0.pos.x;
	double const disty  = obj1.pos.y-obj0.pos.y;
	double const distz  = obj1.pos.z-obj0.pos.z;
	double const dist   = sqrt(distx *distx+disty*disty+distz*distz);
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

void bow_gravobjs(bow_objroot const * const root) {
	for (bow_obj * obj0 = root->objs;obj0 != nullptr;obj0 = obj0->next) 
		for (bow_obj * obj1 = obj0->next;obj1 != nullptr;obj1 = obj1->next) {
			bow_grav(obj0,obj1);
		}
}
