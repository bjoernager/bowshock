// Copyright 2022-2023 Gabriel Jensen.

#include <bow/lgc.h>
#include <bow/run.h>

#include <inttypes.h>

void bow_genSys(bow_objRoot * const sys,zap_i04 const id,zap_i04 const tm) {
	bow_log("generating system (%" PRIXLEAST64 ")",id);

	sys->objs = nullptr;
	bow_obj objtmp;
	objtmp = (bow_obj) {
		.typ     = bow_objTyp_star,
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
		.starTyp = bow_star_g,
		// next will be overwritten anyways.
	};
	bow_addObj(sys,&objtmp);
	objtmp = (bow_obj) {
		.typ     = bow_objTyp_wrld,
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
			.x = 0x1.B2D06FF3p-23*bow_tmMod,
			.y = 0x0p0,
			.z = 0x0p0,
		},
		.rotVel  = {
			.x = 0x0p0,
			.y = 0x0p0,
			.z = 0x1.31DB66BBp-15,
		},
		.mass    = 0x1.931AFC649369998Fp-19,
		.wrldTyp = bow_wrld_rck,
	};
	bow_addObj(sys,&objtmp);
	
	bow_sim(sys,tm);
}
