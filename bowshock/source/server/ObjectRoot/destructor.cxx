// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/server.hxx>

#include <format>
#include <string>

using namespace ::std::literals::string_literals;

bow::ObjectRoot::~ObjectRoot() noexcept {
	::bow::log("server"s, "deleting objects"s);

	::bow::ObjectElement* element;
	::bow::ObjectElement* next;

	for (element = this->elements; element != nullptr; element = next) {
		::bow::log("server"s, ::std::format("deleting object of type {}", element->object->object_type_string()));

		next = element->next;
		delete element;
	}
}
