// Copyright 2022-2023 Gabriel Jensen.

#include <bow/lgc.h>
#include <bow/sav.h>

#include <zap/mem.h>

#include <string.h>

void bow_genDat(bow_plDat * const datptr) {
	bow_log("generating player data");

	bow_plDat dat;
	zap_cp(&dat,datptr,sizeof (dat));
	
	dat.ship.typ  = bow_objTyp_ship;
	dat.ship.mass = bow_shipMass(dat.ship.shipTyp);
	dat.zoom      = 0x4p0;
	
	zap_cp(datptr,&dat,sizeof (dat));
}
