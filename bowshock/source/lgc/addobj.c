#define bow_sym "addobj"

#include <bow/info.h>
#include <bow/lgc.h>

#include <stdlib.h>
#include <zap/mem.h>

bow_obj * bow_addobj(bow_objroot * const root,bow_obj const * const objval) {
	bow_dbglog("adding object of type %s",bow_objtypstr(objval->typ));
	bow_obj * const obj = malloc(sizeof (bow_obj));
	if (obj == nullptr) {
		bow_dbglog("unable to allocate memory for object");
		bow_quit(bow_stat_err);
	}
	zap_cp(obj,objval,sizeof (bow_obj));
	obj->next  = root->objs;
	root->objs = obj;
	return obj;
}
