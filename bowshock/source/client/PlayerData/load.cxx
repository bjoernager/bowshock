// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/client.hxx>
#include <bow/logic.hxx>

#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <fmt/core.h>
#include <stdexcept>
#include <string>

using namespace ::std::literals::string_literals;

auto bow::PlayerData::load(::std::string const& path) -> void {
	::fmt::print(stderr, "[client] loading save file at \"{}\"\n", path);

	::std::array<::std::uint8_t, ::bow::SAVE_LENGTH> raw;

	if (!this->read_file(raw, path)) [[likely]] {
		this->decode_save(*this, raw);

		this->ship.mass = this->ship.net_mass();
	}
}
