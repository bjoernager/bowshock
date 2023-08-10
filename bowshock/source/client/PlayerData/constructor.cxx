// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/client.hxx>
#include <bow/logic.hxx>

#include <cstdint>
#include <string>

using namespace ::std::literals::string_literals;

bow::PlayerData::PlayerData() noexcept {
	::bow::log("client"s, "generating player data"s);

	this->name              = "Corneille"s;
	this->time              = UINT64_C(0x0); // 256 julian years after the Unix Epoch.
	this->system_identifier = UINT64_C(0x0);
	this->ship              = ::bow::Ship();
	this->zoom              = 0x4p0;
}
