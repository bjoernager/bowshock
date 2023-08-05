// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/server.hxx>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fmt/core.h>

template<::bow::ObjectLike T>
auto bow::ServerInstance::add_object(::bow::ObjectRoot& root, T const& object_value) -> void {
	::fmt::print(stderr, "[server] adding object of type {}\n", object_value.object_type_string());

	auto const object = new T;
	*object = object_value;

	object->next = root.objects;
	root.objects = object;
}

template auto ::bow::ServerInstance::add_object<::bow::Canister>(::bow::ObjectRoot& root, ::bow::Canister const& object_value) -> void;
template auto ::bow::ServerInstance::add_object<::bow::Ship>(    ::bow::ObjectRoot& root, ::bow::Ship const&     object_value) -> void;
template auto ::bow::ServerInstance::add_object<::bow::Star>(    ::bow::ObjectRoot& root, ::bow::Star const&     object_value) -> void;
template auto ::bow::ServerInstance::add_object<::bow::Station>( ::bow::ObjectRoot& root, ::bow::Station const&  object_value) -> void;
template auto ::bow::ServerInstance::add_object<::bow::World>(   ::bow::ObjectRoot& root, ::bow::World const&    object_value) -> void;
