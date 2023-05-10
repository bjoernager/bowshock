// Copyright 2022-2023 Gabriel Jensen.

#pragma once

#include <bow/bs.hxx>

namespace bow {
	constexpr ::zp::i04 savver = 0x6u;

	constexpr ::zp::siz savlen = 0x79u+::bow::cmdnamlen;

	constexpr ::zp::i8 maxshpid = static_cast<::zp::i8>(::bow::shp::vip);

	/*
		Save format:

		offset: id:         size [bytes]: format:

		0x00    fmtver     8             unsigned
		0x08    cmdnam     E             UTF-8
		0x16    tim        8             unsigned
		0x1E    sysidt     8             unsigned
		0x1F    shptyp     1             unsigned
		0x27    shpposx    8             binary64
		0x2F    shpposy    8             binary64
		0x37    shpposz    8             binary64
		0x3F    shprotx    8             binary64
		0x47    shproty    8             binary64
		0x4F    shprotz    8             binary64
		0x57    shpposvelx 8             binary64
		0x5F    shpposvely 8             binary64
		0x67    shpposvelz 8             binary64
		0x6F    shprotvelx 8             binary64
		0x77    shprotvely 8             binary64
		0x7F    shprotvelz 8             binary64
	*/

	struct savdat {
		::zp::i04 fmtVer;
		char8_t   cmdnam[::bow::cmdnamlen];
		::zp::i04 tim;
		::zp::i04 sysidt;
		::zp::i8  shptyp;
		::zp::f04 shpposx;
		::zp::f04 shpposy;
		::zp::f04 shpposz;
		::zp::f04 shprotx;
		::zp::f04 shproty;
		::zp::f04 shprotz;
		::zp::f04 shpposvelx;
		::zp::f04 shpposvely;
		::zp::f04 shpposvelz;
		::zp::f04 shprotvelx;
		::zp::f04 shprotvely;
		::zp::f04 shprotvelz;
	};

	auto decsav(::bow::savdat & buf,::zp::i8 const *      dat) noexcept -> void;
	auto encsav(::zp::i8 *      buf,::bow::savdat const & dat) noexcept -> void;

	auto newsav(::bow::pldat & dat) noexcept -> void;

	auto cnt(  ::bow::pldat &  dat,char const * fil) noexcept -> void;
	auto gendat(::bow::pldat & dat)                  noexcept -> void;

	auto sav(char const * fil,::bow::pldat const & dat) noexcept -> void;
}
