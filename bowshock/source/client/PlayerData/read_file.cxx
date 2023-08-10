// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/client.hxx>
#include <bow/logic.hxx>

#include <array>
#include <cstdint>
#include <cstdio>
#include <stdexcept>
#include <string>

using namespace ::std::literals::string_literals;

auto bow::PlayerData::read_file(::std::array<::std::uint8_t, ::bow::SAVE_LENGTH>& buffer, ::std::string const& path) -> bool {
	using ::bow::SAVE_LENGTH;

	auto const file = ::std::fopen(path.c_str(), "rb");

	if (file == nullptr) [[unlikely]] {
		::bow::log("client"s, "unable to open save file, using default"s);
		return true;
	}

	if (::std::fread(buffer.data(), sizeof (::std::uint8_t), SAVE_LENGTH, file) < SAVE_LENGTH) [[unlikely]] {
		throw ::std::runtime_error("unable to read save file"s);
	}

	::std::fclose(file);

	return false;
}
