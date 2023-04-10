// Copyright 2022-2023 Gabriel Jensen.

#include <bow/lgc.hxx>

char const * ::bow::objTypStr(::bow::objTyp const typ) noexcept {
	char const * str;

	switch (typ) {
	case ::bow::objTyp::can:
		str = "canister";
		break;
	case ::bow::objTyp::pl:
		str = "player";
		break;
	case ::bow::objTyp::ship:
		str = "ship";
		break;
	case ::bow::objTyp::star:
		str = "star";
		break;
	case ::bow::objTyp::station:
		str = "station";
		break;
	case ::bow::objTyp::wrld:
		str = "world";
		break;
	}
	
	return str;
}
