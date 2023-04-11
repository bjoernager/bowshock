// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.hxx>

#include <cstdlib>
#include <flux/stats.hh>
#include <zap/mem.hh>
#include <zap/str.hh>

char const * ::bow::bow::getSavPth() noexcept {
	char const * hmDir    = ::flux::hmdir();
	char const * filNm;
	::zap::sz    hmDirLen;
	::zap::sz    filNmLen;
	
	if (hmDir == nullptr) [[unlikely]] {
		bow_log("unable to get home directory, using current directory");
		bow_setStrLen(hmDir,hmDirLen,"./");
	}
	else hmDirLen = ::zap::strlen(hmDir);

	bow_setStrLen(filNm,filNmLen,".save.bowshock");
	
	::zap::sz pthLen = hmDirLen+filNmLen+0x1u;
	
	char * pth = new char[pthLen + 0x1u];
	
	pth = ::zap::bytecp(pth,hmDir,hmDirLen).dest;
	*pth++ = '/';
	pth = ::zap::bytecp(pth,filNm,filNmLen).dest;
	*pth   = '\x00';

	pth -= pthLen;
	
	return pth;
}
