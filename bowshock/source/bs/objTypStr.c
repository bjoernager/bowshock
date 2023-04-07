// Copyright 2022-2023 Gabriel Jensen.

#include <bow/lgc.h>

char const * bow_objTypStr(bow_objTyp const typ) {
	char const * str;
	switch (typ) {
	case bow_objTyp_can:
		str = "canister";
		break;
	case bow_objTyp_pl:
		str = "player";
		break;
	case bow_objTyp_ship:
		str = "ship";
		break;
	case bow_objTyp_star:
		str = "star";
		break;
	case bow_objTyp_station:
		str = "station";
		break;
	case bow_objTyp_wrld:
		str = "world";
		break;
	}
	return str;
}
