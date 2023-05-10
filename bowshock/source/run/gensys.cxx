// Copyright 2022-2023 Gabriel Jensen.

#include <bow/lgc.hxx>
#include <bow/run.hxx>

#include <cinttypes>

auto ::bow::gensys(::bow::objroot & sys,::zp::i04 const id,::zp::i04 const tim) -> void {
	bow_log("generating system (%" PRIX64 ")",id);

	// Note: The following code is only temporary;
	sys.objs = nullptr;
	::bow::obj objTmp;
	objTmp = ::bow::obj {
		.typ     = ::bow::objtyp::tar,
		.tartyp = ::bow::tar::g,
		.pos     = {
			.x = 0x0p0,
			.y = 0x0p0,
			.z = 0x0p0,
		},
		.rot     = {
			.x = 0x0p0,
			.y = 0x0p0,
			.z = 0x0p0,
		},
		.posVel  = {
			.x = 0x0p0,
			.y = 0x0p0,
			.z = 0x0p0,
		},
		.rotVel  = {
			.x = 0x0p0,
			.y = 0x0p0,
			.z = 0x0p0,
		},
		.mas    = 0x1p0,
		// nxt will be overwritten anyways.
	};
	::bow::addobj(sys,objTmp);
	objTmp = ::bow::obj {
		.typ     = ::bow::objtyp::wrl,
		.wrldTyp = ::bow::wrl::rck,
		.pos     = {
			.x = 0x0p0,
			.y = 0x1.F76F144Dp-1,
			.z = 0x0p0,
		},
		.rot     = {
			.x = 0x0p0,
			.y = 0x0p0,
			.z = 0x0p0,
		},
		.posVel  = {
			.x = 0x1.B2D06FF3p-23*::bow::timmod,
			.y = 0x0p0,
			.z = 0x0p0,
		},
		.rotVel  = {
			.x = 0x0p0,
			.y = 0x0p0,
			.z = 0x1.31DB66BBp-15,
		},
		.mas    = 0x1.931AFC649369998Fp-19,
	};
	::bow::addobj(sys,objTmp);

	::bow::sim(sys,tim);
}
