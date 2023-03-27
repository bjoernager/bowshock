#define bow_sym "objtypstr"

#include <bow/info.h>

#include <stddef.h>

char const * bow_objtypstr(bow_objtyp const typ) {
	char const * str;
	switch (typ) {
	default:
		unreachable();
	case bow_objtyp_can:
		str = "canister";
		break;
	case bow_objtyp_play:
		str = "player";
		break;
	case bow_objtyp_sat:
		str = "satellite";
		break;
	case bow_objtyp_ship:
		str = "ship";
		break;
	case bow_objtyp_star:
		str = "star";
		break;
	case bow_objtyp_station:
		str = "station";
		break;
	case bow_objtyp_wrld:
		str = "world";
		break;
	}
	return str;
}
