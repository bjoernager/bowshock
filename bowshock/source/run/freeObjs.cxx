// Copyright 2022-2023 Gabriel Jensen.

#include <bow/run.hxx>

void ::bow::freeObjs(::bow::objRoot const & root) noexcept {
	bow_logDbg("freeing objects");
	
	::bow::obj * obj;
	::bow::obj * next;
	for (obj = root.objs;obj != nullptr;obj = next) {
		bow_logDbg("freeing object of type %s",::bow::objTypStr(obj->typ));
		
		next = obj->next;
		delete obj;
	}
}
