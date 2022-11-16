#include <acm/evt.h>
#include <acm/info.h>

#include <stdint.h>

bool acm_jmp(uint_least64_t const _sys) {
	acm_pldat pldat = acm_dat.pldat;
	if (acm_sysdist(_sys) > acm_jmplen(&pldat.ship)) {
		return true;
	}
	acm_dat.pldat = pldat;
	return false;
}
