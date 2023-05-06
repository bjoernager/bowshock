// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.hxx>

#include <cstdlib>
#include <ly/fs>
#include <zp/mem>
#include <zp/str>

char const * ::bow::bow::getSavPth() noexcept {
	char const * homdir    = ::ly::homdir();
	char const * filNm;
	::zp::siz    hmDirLen;
	::zp::siz    filNmLen;
	
	if (homdir == nullptr) [[unlikely]] {
		bow_log("unable to get home directory, using current directory");
		bow_setStrLen(homdir,hmDirLen,"./");
	}
	else hmDirLen = ::zp::strlen(homdir);

	bow_setStrLen(filNm,filNmLen,".save.bowshock");
	
	::zp::siz pthLen = hmDirLen+filNmLen+0x1u;
	
	char * pth = new char[pthLen + 0x1u];
	
	pth = ::zp::memcpy(pth,homdir,hmDirLen).dst;
	*pth++ = '/';
	pth = ::zp::memcpy(pth,filNm,filNmLen).dst;
	*pth   = '\x00';

	pth -= pthLen;
	
	return pth;
}
