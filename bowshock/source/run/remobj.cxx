// Copyright 2022-2023 Gabriel Jensen.

#include <bow/run.hxx>

auto ::bow::remobj(::bow::objroot const & root) noexcept -> void {
	bow_logdbg("freeing objects");
	
	::bow::obj * obj;
	::bow::obj * nxt;
	for (obj = root.objs;obj != nullptr;obj = nxt) {
		bow_logdbg("freeing object of type %s",::bow::objtypstr(obj->typ));
		
		nxt = obj->nxt;
		delete obj;
	}
}
