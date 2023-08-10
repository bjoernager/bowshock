// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/client.hxx>

#include <array>
#include <cstdint>
#include <cstdio>
#include <format>
#include <string>

using namespace ::std::literals::string_literals;

auto bow::PlayerData::save(::std::string const& path) -> void {
	using ::bow::SAVE_LENGTH;

	::bow::log("client"s, ::std::format("saving CMDR {} at \"{}\"", this->name.data(), path));

	::std::array<::std::uint8_t, SAVE_LENGTH> data;

	::bow::PlayerData::encode_save(data, *this);

	this->write_file(path, data);
}
