// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/client.hxx>
#include <bow/logic.hxx>

#include <array>
#include <cstdint>
#include <cstdio>
#include <fmt/core.h>
#include <stdexcept>
#include <string>

auto bow::PlayerData::read_file(::std::array<::std::uint8_t, ::bow::SAVE_LENGTH>& buffer, ::std::string const& path) -> bool {
	using ::bow::SAVE_LENGTH;

	auto const file = ::std::fopen(path.c_str(), "rb");

	if (file == nullptr) [[unlikely]] {
		::fmt::print(stderr, "[client] unable to open save file, using default\n");

		return true;
	}

	if (::std::fread(buffer.data(), sizeof (::std::uint8_t), SAVE_LENGTH, file) < SAVE_LENGTH) [[unlikely]] {
		throw ::std::runtime_error("unable to read save file");
	}

	::std::fclose(file);

	return false;
}
