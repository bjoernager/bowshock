// Copyright 2022-2023 Gabriel Jensen.

#include <bow/run.hxx>

#include <cstdlib>
#include <zp/mem>

auto ::bow::addobj(::bow::objroot & root,::bow::obj const & objVal) -> void {
	bow_logdbg("adding object of type %s",::bow::objtypstr(objVal.typ));

	::bow::obj * const obj = new ::bow::obj;
	::zp::memcpy(obj,&objVal,sizeof (objVal));

	obj->nxt = root.objs;
	root.objs = obj;
}
