// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/runtime.hxx>

#include <cstdio>
#include <fmt/core.h>

auto ::bow::delete_objects(::bow::ObjectRoot const& root) noexcept -> void {
	::fmt::print(stderr, "freeing objects\n");

	::bow::Object* object;
	::bow::Object* next;

	for (object = root.objects; object != nullptr; object = next) {
		::fmt::print(stderr, "freeing object of type {}\n", ::bow::object_type_string(object->type));

		next = object->next;
		delete object;
	}
}
