// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/runtime.hxx>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fmt/core.h>

auto ::bow::add_object(::bow::ObjectRoot& root, ::bow::Object const& object_value) -> void {
	::fmt::print(stderr, "adding object of type {}\n", ::bow::object_type_string(object_value.type));

	::bow::Object* const object = new ::bow::Object;
	::std::memcpy(object, &object_value, sizeof (object_value));

	object->next = root.objects;
	root.objects = object;
}
