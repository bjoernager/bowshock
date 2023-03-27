#define bow_sym "freeobjs"

#include <bow/info.h>
#include <bow/lgc.h>

#include <stdlib.h>
#include <zap/mem.h>

void bow_freeobjs(bow_objroot const * const root) {
	bow_dbglog("freeing objects");
	bow_obj * obj = root->objs;
	bow_obj * next;
	while (obj != nullptr) {
		bow_dbglog("freeing object of type %s",bow_objtypstr(obj->typ));
		next = obj->next;
		free(obj);
		obj = next;
	}
}
