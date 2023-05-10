// Copyright 2022-2023 Gabriel Jensen.

#include <bow/lgc.hxx>

auto ::bow::objtypstr(::bow::objtyp const typ) noexcept -> char const * {
	char const * str;

	switch (typ) {
	case ::bow::objtyp::can:
		str = "canister";
		break;
	case ::bow::objtyp::ply:
		str = "player";
		break;
	case ::bow::objtyp::shp:
		str = "ship";
		break;
	case ::bow::objtyp::tar:
		str = "star";
		break;
	case ::bow::objtyp::stn:
		str = "station";
		break;
	case ::bow::objtyp::wrl:
		str = "world";
		break;
	}
	
	return str;
}
