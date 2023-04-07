// Copyright 2022-2023 Gabriel Jensen.

#include <bow/run.h>

#include <stdlib.h>
#include <zap/mem.h>

void bow_freeObjs(bow_objRoot * const root) {
	bow_dbgLog("freeing objects");
	bow_obj * obj;
	bow_obj * next;
	for (obj = root->objs;obj != nullptr;obj = next) {
		bow_dbgLog("freeing object of type %s",bow_objTypStr(obj->typ));
		next = obj->next;
		free(obj);
	}
}
