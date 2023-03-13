#define bow_sym "grav"

#include <bow/lgc.h>

#include <math.h>
#include <zap/mem.h>

void bow_mv(bow_obj * objptr) {
	bow_obj obj;
	zap_cp(&obj,objptr,sizeof (obj));
	obj.pos.x += obj.vel.x;
	obj.pos.y += obj.vel.y;
	obj.pos.z += obj.vel.z;
	zap_cp(objptr,&obj,sizeof (obj));
}
