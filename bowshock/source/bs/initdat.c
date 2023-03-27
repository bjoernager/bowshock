#define bow_sym "initdat"

#include <bow/sav.h>

#include <flux/stats.h>
#include <stdlib.h>
#include <zap/mem.h>
#include <zap/str.h>

#define bow_setstr(ptr,len,str) ((void)(ptr = str,len = sizeof (str)))

static char * bow_getsavpth(void) {
	char const * hmdir    = flux_hmdir();
	zap_sz       hmdirlen;
	char const * filnm;
	zap_sz       filnmlen;
	if (hmdir == nullptr) {
		bow_log("unable to get home directory");
		bow_setstr(hmdir,hmdirlen,"./");
	}
	else hmdirlen = zap_strlen(hmdir);
	bow_setstr(filnm,filnmlen,".save.bowshock");
	zap_sz pthsz = hmdirlen+filnmlen+0x2u;
	char * pth = malloc(pthsz);
	if (pth == nullptr) {
		bow_log("unable to allocate memory");
		bow_quit(bow_stat_err);
	}
	zap_cp(pth,hmdir,hmdirlen);
	pth += hmdirlen;
	*pth++ = '/';
	zap_cp(pth,filnm,filnmlen);
	pth += filnmlen;
	*pth++ = '\x0';
	pth -= pthsz;
	return pth;
}

void bow_initdat(bow_playdat * const playdatptr,char const * * const savpthptr) {
	bow_log("initialising data");
	char const * savpth = bow_getsavpth();
	bow_playdat playdat;
	bow_cont(savpth,&playdat);
	bow_gendat(&playdat);
	*savpthptr = savpth;
	zap_cp(playdatptr,&playdat,sizeof (playdat));
}
