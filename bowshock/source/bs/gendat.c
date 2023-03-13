#define bow_sym "gendat"

#include <bow/info.h>

#include <flux.h>
#include <zap/mem.h>

#include <string.h>

void bow_gendat(bow_playdat * const playdatptr) {
	bow_log("generating data");
	bow_playdat playdat;
	memcpy(&playdat,playdatptr,sizeof (playdat));
	playdat.ship.mass = bow_shipmass(playdat.ship.shiptyp);
	memcpy(playdatptr,&playdat,sizeof (playdat));
}
