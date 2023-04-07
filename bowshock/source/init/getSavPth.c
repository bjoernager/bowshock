// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.h>

#include <flux/stats.h>
#include <stdlib.h>
#include <zap/mem.h>
#include <zap/str.h>

char const * bow_getSavPth(void) {
	char const * hmDir    = flux_hmdir();
	char const * filNm;
	zap_sz       hmDirLen;
	zap_sz       filNmLen;
	
	unlikely (hmDir == nullptr) {
		bow_log("unable to get home directory");
		bow_setStrLen(hmDir,hmDirLen,"./");
	}
	else hmDirLen = zap_strlen(hmDir);

	bow_setStrLen(filNm,filNmLen,".save.bowshock");
	
	zap_sz pthLen = hmDirLen+filNmLen+0x1u;
	char * pth    = malloc(pthLen + 0x1u);
	
	unlikely (pth == nullptr) {
		bow_log("unable to allocate memory");
		bow_abrt();
	}

	pth = zap_cp(pth,hmDir,hmDirLen).dest;
	*pth++ = '/';
	pth = zap_cp(pth,filNm,filNmLen).dest;
	*pth   = '\x00';

	pth -= pthLen;
	
	return pth;
}
