// Copyright 2022-2023 Gabriel Jensen.

#include <bow/lgc.h>

#include <inttypes.h>

void bow_sim(bow_objRoot * const sys,zap_i04 const dur) {
	bow_log("simulating for (%" PRIXLEAST64 ") time units",dur);
	
	for (zap_i04 i = 0x0u;i <= dur;++i) {
		bow_gravSys(sys);
		bow_mvObjs(sys);
	}
}
