// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/server.hxx>
#include <bow/logic.hxx>

auto bow::ServerInstance::move(::bow::ObjectRoot& root) noexcept -> void {
	for (auto& object: root) {
		object.position.x += object.positional_velocity.x;
		object.position.y += object.positional_velocity.y;
		object.position.z += object.positional_velocity.z;
		object.rotation.x += object.rotational_velocity.x;
		object.rotation.y += object.rotational_velocity.y;
		object.rotation.z += object.rotational_velocity.z;
	}
}
