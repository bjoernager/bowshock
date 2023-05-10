// Copyright 2022-2023 Gabriel Jensen.

#include <bow/lgc.hxx>

#include <bow/run.hxx>

#include <cinttypes>

auto ::bow::sim(::bow::objroot & sys,::zp::i04 const dur) noexcept -> void {
	bow_log("simulating for (%" PRIX64 ") time units",dur);

	for (::zp::i04 i = 0x0u;i <= dur;++i) {
		::bow::grv(sys);
		::bow::mov(sys);
	}
}
