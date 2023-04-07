// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.h>

#include <inttypes.h>
#include <time.h>
#include <stdlib.h>

void bow_priQuot(void) {
	srand((unsigned int)time(nullptr));
	zap_i8 const quotId = (zap_i8)rand() % 0x22u;
	
	char const * quot;
	char const * src;

	unlikely (bow_getQuot(&quot,&src,quotId)) {
		bow_logErr("invalid quote identifier (%" PRIXLEAST8 ")",quotId);
		bow_getQuot(&quot,&src,0x0u);
	}
	
	bow_rawlog("\n%s\n\u2014 %s\n\n",quot,src);
}
