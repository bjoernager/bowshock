// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.hxx>

#include <cinttypes>
#include <ctime>
#include <cstdlib>

void ::bow::bow::priQuot() noexcept {
	::std::srand(static_cast<unsigned int>(::std::time(nullptr)));
	::zap::i8 const quotId = (::zap::i8)rand() % 0x24u;
	
	char const * quot;
	char const * src;
	getQuot(&quot,&src,quotId);
	
	if (src == nullptr) {bow_logRaw("%s\n",quot);}
	else {bow_logRaw("\n%s\n\u2014 %s\n\n",quot,src);}
}
