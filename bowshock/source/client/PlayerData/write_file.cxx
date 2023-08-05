// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/client.hxx>

#include <array>
#include <cstdint>
#include <cstdio>
#include <stdexcept>

auto bow::PlayerData::write_file(::std::string const& path, ::std::array<::std::uint8_t, ::bow::SAVE_LENGTH> const& data) -> void {
	using ::bow::SAVE_LENGTH;

	auto const file = ::std::fopen(path.c_str(), "wb");
	if (file == nullptr) [[unlikely]] {
		throw ::std::runtime_error("unable to create save file");
	}

	if (::std::fwrite(data.data(), 0x1u, SAVE_LENGTH, file) < SAVE_LENGTH) [[unlikely]] {
		throw ::std::runtime_error("unable to write save file");
	}

	::std::fclose(file);
}
