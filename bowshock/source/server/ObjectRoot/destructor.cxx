// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/server.hxx>

#include <cstdio>
#include <fmt/core.h>
#include <type_traits>

bow::ObjectRoot::~ObjectRoot() noexcept {
	::fmt::print(stderr, "[server] deleting objects\n");

	::bow::ObjectElement* element;
	::bow::ObjectElement* next;

	for (element = this->elements; element != nullptr; element = next) {
		::fmt::print(stderr, "[server] deleting object of type {}\n", element->object->object_type_string());

		next = element->next;
		delete element;
	}
}
