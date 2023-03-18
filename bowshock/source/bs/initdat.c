#define bow_sym "initdat"

#include <bow/bs.h>

#include <flux.h>
#include <stdlib.h>
#include <string.h>
#include <zap/mem.h>
#include <zap/str.h>

#define bow_setstr(ptr,len,str) ((void)(ptr = str,len = sizeof (str)))

static char * bow_getsavpth(void) {
	char const * hmdir    = getenv("HOME");
	zap_sz       hmdirlen;
	char const * filnm;
	zap_sz       filnmlen;
	if (hmdir == nullptr) {
		bow_log("unable to get home directory");
		bow_setstr(hmdir,hmdirlen,"./");
	}
	else hmdirlen = zap_strlen(hmdir);
	bow_setstr(filnm,filnmlen,".save.bowshock");
	zap_sz pthsz = hmdirlen + filnmlen + 0x2u;
	char * pth = malloc(pthsz);
	if (pth == nullptr) {
		bow_log("unable to allocate memory");
		bow_quit(bow_stat_err);
	}
	memcpy(pth,hmdir,hmdirlen);
	pth += hmdirlen;
	*pth++ = '/';
	memcpy(pth,filnm,filnmlen);
	pth += filnmlen;
	*pth++ = '\x0';
	pth -= pthsz;
	return pth;
}

void bow_initdat(bow_playdat * const playdatptr,char const * * const savpthptr) {
	bow_log("initialising data");
	char const * savpth = bow_getsavpth();
	bow_playdat playdat = {
		.nm    = "Caelum\x0\x0\x0\x0\x0\x0\x0\x0\x0",
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
	*savpthptr = savpth;
	memcpy(playdatptr,&playdat,sizeof (playdat));
}
