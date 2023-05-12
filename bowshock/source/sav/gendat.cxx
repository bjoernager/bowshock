// Copyright 2022-2023 Gabriel Jensen.

#include <bow/lgc.hxx>
#include <bow/sav.hxx>

auto ::bow::gendat(::bow::plydat & dat) noexcept -> void {
	bow_log("generating player data");

	dat.shp.typ = ::bow::objtyp::shp;
	dat.shp.mas = ::bow::shpmas(dat.shp.shptyp);
	dat.zom     = 0x4p0;
}
