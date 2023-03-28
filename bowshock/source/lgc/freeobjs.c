// Copyright 2022-2023 Gabriel Jensen.

#include <bow/info.h>
#include <bow/lgc.h>

#include <stdlib.h>
#include <zap/mem.h>

void bow_freeobjs(bow_objroot const * const root) {
	bow_dbglog("freeing objects");
	bow_obj * obj;
	bow_obj * next;
	for (obj = root->objs;obj != nullptr;obj = next) {
		bow_dbglog("freeing object of type %s",bow_objtypstr(obj->typ));
		next = obj->next;
		free(obj);
	}
}
