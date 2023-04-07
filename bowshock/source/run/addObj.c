// Copyright 2022-2023 Gabriel Jensen.

#include <bow/run.h>

#include <stdlib.h>
#include <zap/mem.h>

bow_obj * bow_addObj(bow_objRoot * const root,bow_obj const * const objval) {
	bow_dbgLog("adding object of type %s",bow_objTypStr(objval->typ));

	bow_obj * const obj = malloc(sizeof (bow_obj));
	unlikely (obj == nullptr) {
		bow_logErr("unable to allocate memory for object");
		bow_abrt();
	}
	zap_cp(obj,objval,sizeof (bow_obj));
	obj->next  = root->objs;
	root->objs = obj;
	
	return obj;
}
