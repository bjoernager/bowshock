#define bow_sym "gendat"

#include <bow/info.h>

#include <zap/mem.h>

#include <string.h>

void bow_gendat(bow_playdat * const playdatptr) {
	bow_log("generating data");
	bow_playdat playdat;
	zap_cp(&playdat,playdatptr,sizeof (playdat));
	playdat.ship.typ  = bow_objtyp_ship;
	playdat.ship.mass = bow_shipmass(playdat.ship.shiptyp);
	zap_cp(playdatptr,&playdat,sizeof (playdat));
}
