// Copyright 2022-2023 Gabriel Jensen.

#include <bow/ini.hxx>

#include <cinttypes>
#include <ctime>
#include <cstdlib>

auto ::bow::bow::priquo() noexcept -> void {
	::std::srand(static_cast<unsigned int>(::std::time(nullptr)));
	::zp::i8 const quotId = (::zp::i8)rand() % 0x24u;
	
	char const * quo;
	char const * src;
	getquo(&quo,&src,quotId);
	
	if (src == nullptr) {bow_lograw("%s\n",quo);}
	else                {bow_lograw("\n%s\n\u2014 %s\n\n",quo,src);}
}
