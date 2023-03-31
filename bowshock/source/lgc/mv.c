// Copyright 2022-2023 Gabriel Jensen.

#include <bow/lgc.h>

#include <math.h>
#include <zap/mem.h>

void bow_mv(bow_obj * obj) {
	obj->pos.x += obj->posvel.x;
	obj->pos.y += obj->posvel.y;
	obj->pos.z += obj->posvel.z;
	obj->rot.x += obj->rotvel.x;
	obj->rot.y += obj->rotvel.y;
	obj->rot.z += obj->rotvel.z;
}

void bow_mvobjs(bow_objroot * root) {
	for (bow_obj * obj = root->objs;obj != nullptr;obj = obj->next)
		bow_mv(obj);
}
