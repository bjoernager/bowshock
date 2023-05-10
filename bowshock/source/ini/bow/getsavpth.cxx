// Copyright 2022-2023 Gabriel Jensen.

#include <bow/ini.hxx>

#include <cstdlib>
#include <ly/fs>
#include <zp/mem>
#include <zp/str>

auto ::bow::bow::getsavpth() noexcept -> char const * {
	char const * homdir    = ::ly::homdir();
	char const * filnam;
	::zp::siz    homdirlen;
	::zp::siz    filnamlen;
	
	if (homdir == nullptr) [[unlikely]] {
		bow_log("unable to get home directory, using current directory");
		bow_setstrlen(homdir,homdirlen,"./");
	}
	else homdirlen = ::zp::strlen(homdir);

	bow_setstrlen(filnam,filnamlen,".save.bowshock");
	
	::zp::siz pthlen = homdirlen+filnamlen+0x1u;
	
	char * pth = new char[pthlen + 0x1u];
	
	pth = ::zp::memcpy(pth,homdir,homdirlen).dst;
	*pth++ = '/';
	pth = ::zp::memcpy(pth,filnam,filnamlen).dst;
	*pth   = '\x00';

	pth -= pthlen;
	
	return pth;
}
