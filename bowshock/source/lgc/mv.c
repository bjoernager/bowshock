// Copyright 2022-2023 Gabriel Jensen.

#include <bow/lgc.h>

#include <math.h>
#include <zap/mem.h>

void bow_mv(bow_obj * obj) {
	obj->pos.x += obj->posVel.x;
	obj->pos.y += obj->posVel.y;
	obj->pos.z += obj->posVel.z;
	obj->rot.x += obj->rotVel.x;
	obj->rot.y += obj->rotVel.y;
	obj->rot.z += obj->rotVel.z;
}

void bow_mvObjs(bow_objRoot * root) {
	for (bow_obj * obj = root->objs;obj != nullptr;obj = obj->next)
		bow_mv(obj);
}
