// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/server.hxx>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fmt/core.h>

template<::bow::ObjectLike T>
auto bow::ObjectRoot::add(T const& object_value) -> T* {
	::fmt::print(stderr, "[server] adding object of type {}\n", object_value.object_type_string());

	// Ignore exceptions:
	auto const element = new ::bow::ObjectElement;
	element->object    = new T;
	*element->object   = object_value;

	element->next = this->elements;
	this->elements = element;

	return static_cast<T*>(element->object);
}

template auto ::bow::ObjectRoot::add<::bow::Canister>(::bow::Canister const& object_value) -> ::bow::Canister*;
template auto ::bow::ObjectRoot::add<::bow::Ship>(    ::bow::Ship const&     object_value) -> ::bow::Ship*;
template auto ::bow::ObjectRoot::add<::bow::Star>(    ::bow::Star const&     object_value) -> ::bow::Star*;
template auto ::bow::ObjectRoot::add<::bow::Station>( ::bow::Station const&  object_value) -> ::bow::Station*;
template auto ::bow::ObjectRoot::add<::bow::World>(   ::bow::World const&    object_value) -> ::bow::World*;
