// Copyright 2022-2023 Gabriel Jensen.

#include <bow/lgc.h>

#include <inttypes.h>

void bow_gensys(bow_objroot * const sys,zap_i04 const id,zap_i04 const tm) {
	bow_log("generating system (%" PRIXLEAST64 ")",id);
	sys->objs = nullptr;
	bow_obj objtmp;
	objtmp = (bow_obj) {
		.typ     = bow_objtyp_star,
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
		.posvel  = {
			.x = 0x0p0,
			.y = 0x0p0,
			.z = 0x0p0,
		},
		.rotvel  = {
			.x = 0x0p0,
			.y = 0x0p0,
			.z = 0x0p0,
		},
		.mass    = 0x19'1930'A5E7'5F0C'1918'1400'0000p0,
		.startyp = bow_star_g,
		// next will be overwritten anyways.
	};
	bow_addobj(sys,&objtmp);
	objtmp = (bow_obj) {
		.typ     = bow_objtyp_wrld,
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
		.posvel  = {
			.x = 0x1.B2D06FF3p-23*bow_tmmod,
			.y = 0x0p0,
			.z = 0x0p0,
		},
		.rotvel  = {
			.x = 0x0p0,
			.y = 0x0p0,
			.z = 0x1.31DB66BBp-15,
		},
		.mass    = 0x4'F0A9'9C58'8848'32A0'0000p0,
		.wrldtyp = bow_wrld_rck,
	};
	bow_addobj(sys,&objtmp);
	bow_sim(sys,tm);
}
