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

bow::PlayerData::PlayerData() noexcept  {
	::fmt::print(stderr, "[client] generating player data\n");

	this->name              = "Corneille"s;
	this->time              = UINT64_C(0x0); // 256 julian years after the Unix Epoch.
	this->system_identifier = UINT64_C(0x0);
	this->ship              = ::bow::Ship();
	this->zoom              = 0x4p0;
}
