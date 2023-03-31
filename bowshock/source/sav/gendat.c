// Copyright 2022-2023 Gabriel Jensen.

#include <bow/lgc.h>
#include <bow/sav.h>

#include <zap/mem.h>

#include <string.h>

void bow_gendat(bow_playdat * const datptr) {
	bow_log("generating player data");
	bow_playdat dat;
	zap_cp(&dat,datptr,sizeof (dat));
	dat.ship.typ  = bow_objtyp_ship;
	dat.ship.mass = bow_shipmass(dat.ship.shiptyp);
	zap_cp(datptr,&dat,sizeof (dat));
}
