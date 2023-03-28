// Copyright 2022-2023 Gabriel Jensen.

#include <bow/bs.h>

#include <flux/stats.h>
#include <stdlib.h>
#include <zap/mem.h>
#include <zap/str.h>

#define bow_setstrlen(ptr,len,str) ((void)(ptr = str,len = sizeof (str)))

char const * bow_getsavpth(void) {
	char const * hmdir    = flux_hmdir();
	zap_sz       hmdirlen;
	char const * filnm;
	zap_sz       filnmlen;
	if (hmdir == nullptr) {
		bow_log("unable to get home directory");
		bow_setstrlen(hmdir,hmdirlen,"./");
	}
	else hmdirlen = zap_strlen(hmdir);
	bow_setstrlen(filnm,filnmlen,".save.bowshock");
	zap_sz pthsz = hmdirlen+filnmlen+0x2u;
	char * pth = malloc(pthsz);
	if (pth == nullptr) {
		bow_log("unable to allocate memory");
		bow_abrt();
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
