// Copyright 2022-2023 Gabriel Jensen.

#include <bow/run.hxx>

#include <cstdlib>
#include <zp/mem>

void ::bow::addObj(::bow::objRoot & root,::bow::obj const & objVal) {
	bow_logDbg("adding object of type %s",::bow::objTypStr(objVal.typ));

	::bow::obj * const obj = new ::bow::obj;
	::zp::memcpy(obj,&objVal,sizeof (objVal));

	obj->next = root.objs;
	root.objs = obj;
}
