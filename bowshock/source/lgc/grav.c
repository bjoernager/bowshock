#define bow_sym "grav"

#include <bow/lgc.h>

#include <math.h>
#include <zap/mem.h>

void bow_grav(bow_obj * objptr,bow_obj const * parptr) {
	bow_obj obj;
	bow_obj par;
	zap_cp(&obj,objptr,sizeof (obj));
	zap_cp(&par,parptr,sizeof (par));
	double const distx = par.pos.x-obj.pos.x;
	double const disty = par.pos.y-obj.pos.y;
	double const distz = par.pos.z-obj.pos.z;
	double const dist  = sqrt(distx*distx+disty*disty+distz*distz);
	double const acc   = bow_gravconst*par.mass/pow(dist,2.0);
	double const angy  = atan2(disty,distx);
	double const angz  = atan2(distz,distx);
	double const vx    = cos(angy)*acc;
	double const vy    = sin(angy)*acc;
	double const vz    = sin(angz)*acc;
	obj.vel.x += vx;
	obj.vel.y += vy;
	obj.vel.z += vz;
	zap_cp(objptr,&obj,sizeof (obj));
}
