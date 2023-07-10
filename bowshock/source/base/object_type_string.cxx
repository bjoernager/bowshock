// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/base.hxx>

#include <string>

using namespace ::std::literals::string_literals;

auto ::bow::object_type_string(::bow::ObjectType const type) noexcept -> ::std::string {
	switch (type) {
	case ::bow::ObjectType::Canister:
		return "canister"s;

	case ::bow::ObjectType::Player:
		return "player"s;

	case ::bow::ObjectType::Ship:
		return "ship"s;

	case ::bow::ObjectType::Star:
		return "star"s;

	case ::bow::ObjectType::Station:
		return "station"s;

	case ::bow::ObjectType::World:
		return "world"s;
	}
}
