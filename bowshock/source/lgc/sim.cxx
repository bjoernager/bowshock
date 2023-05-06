// Copyright 2022-2023 Gabriel Jensen.

#include <bow/lgc.hxx>

#include <bow/run.hxx>

#include <cinttypes>

void ::bow::sim(::bow::objRoot & sys,::zp::i04 const dur) noexcept {
	bow_log("simulating for (%" PRIX64 ") time units",dur);

	for (::zp::i04 i = 0x0u;i <= dur;++i) {
		::bow::grav(sys);
		::bow::mv(sys);
	}
}
