#define bow_sym "initdat"

#include <bow/bs.h>

#include <flux.h>
#include <zap/mem.h>

#include <string.h>

void bow_initdat(bow_playdat * const playdatptr) {
	bow_log("initialising data");
	bow_playdat playdat = {
		.sysid = 0x0u,
		.ship  = {
			.typ     = bow_objtyp_ship,
			.pos     = {
				.x = 0x0.0p0,
				.y = 0x0.0p0,
				.z = 0x0.0p0,
			},
			.vel     = {
				.x = 0x0.0p0,
				.y = 0x0.0p0,
				.z = 0x0.0p0,
			},
			.shiptyp = bow_ship_aq,
		},
	};
	bow_gendat(&playdat);
	memcpy(playdatptr,&playdat,sizeof (playdat));
}
