// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/server.hxx>

#include <cstdio>
#include <fmt/core.h>
#include <type_traits>

auto bow::ServerInstance::delete_objects(::bow::ObjectRoot const& root) noexcept -> void {
	::fmt::print(stderr, "[server] deleting objects\n");

	::bow::Object* object;
	::bow::Object* next;

	for (object = root.objects; object != nullptr; object = next) {
		::fmt::print(stderr, "[server] deleting object of type {}\n", object->object_type_string());

		next = object->next;
		delete object;
	}
}
