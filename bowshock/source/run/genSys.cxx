// Copyright 2022-2023 Gabriel Jensen.

#include <bow/lgc.hxx>
#include <bow/run.hxx>

#include <cinttypes>

void ::bow::genSys(::bow::objRoot & sys,::zap::i04 const id,::zap::i04 const tm) {
	bow_log("generating system (%" PRIXLEAST64 ")",id);

	sys.objs = nullptr;
	::bow::obj objTmp;
	objTmp = {
		.typ     = ::bow::objTyp::star,
		.starTyp = ::bow::star::g,
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
		.mass    = 0x1p0,
		// next will be overwritten anyways.
	};
	::bow::addObj(sys,objTmp);
	objTmp = {
		.typ     = ::bow::objTyp::wrld,
		.wrldTyp = ::bow::wrld::rck,
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
			.x = 0x1.B2D06FF3p-23*::bow::tmMod,
			.y = 0x0p0,
			.z = 0x0p0,
		},
		.rotVel  = {
			.x = 0x0p0,
			.y = 0x0p0,
			.z = 0x1.31DB66BBp-15,
		},
		.mass    = 0x1.931AFC649369998Fp-19,
	};
	::bow::addObj(sys,objTmp);

	::bow::sim(sys,tm);
}
