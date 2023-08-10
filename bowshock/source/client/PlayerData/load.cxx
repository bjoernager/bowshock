// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/client.hxx>
#include <bow/logic.hxx>

#include <array>
#include <cstdint>
#include <format>
#include <string>

using namespace ::std::literals::string_literals;

auto bow::PlayerData::load(::std::string const& path) -> void {
	::bow::log("client"s, ::std::format("loading save file at \"{}\"", path));

	::std::array<::std::uint8_t, ::bow::SAVE_LENGTH> raw;

	if (!this->read_file(raw, path)) [[likely]] {
		this->decode_save(*this, raw);

		this->ship.mass = this->ship.net_mass();
	}
}
