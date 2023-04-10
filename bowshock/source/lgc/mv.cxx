// Copyright 2022-2023 Gabriel Jensen.

#include <bow/lgc.hxx>

void ::bow::mv(::bow::objRoot & root) noexcept {
	auto const mv = [](::bow::obj & obj) {
		obj.pos.x += obj.posVel.x;
		obj.pos.y += obj.posVel.y;
		obj.pos.z += obj.posVel.z;
		obj.rot.x += obj.rotVel.x;
		obj.rot.y += obj.rotVel.y;
		obj.rot.z += obj.rotVel.z;
	};

	for (::bow::obj * obj = root.objs;obj != nullptr;obj = obj->next) {
		mv(*obj);
	}
}
