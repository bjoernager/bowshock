// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/logic.hxx>
#include <bow/save.hxx>

#include <cstdio>
#include <fmt/core.h>

auto ::bow::generate_data(::bow::PlayerData& data) noexcept -> void {
	::fmt::print(stderr, "generating player data\n");

	data.ship.type = ::bow::ObjectType::Ship;
	data.ship.mass = ::bow::ship_mass(data.ship.ship_type);
	data.zoom      = 0x4p0;
}
