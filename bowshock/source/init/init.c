// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.h>
#include <bow/lgc.h>
#include <bow/run.h>
#include <bow/sav.h>

#include <inttypes.h>
#include <stdlib.h>
#include <zap/str.h>

void bow_init(int const argc,char const * const * const argv) {
	bow_termOpts opts;
	bow_chkParams(&opts,argc,argv);
	
	bow_priQuot();
	
	bow_rawlog("\x1B[0m\x1B[1mBowshock\x1B[0m %" PRIXLEAST64 ".%" PRIXLEAST64 ".%" PRIXLEAST64 " \u2013 Copyright 2022\u20102023 \x1B[1mGabriel Jensen\x1B[0m.\n\n",bow_verMaj,bow_verMin,bow_verPat);
	
	bow_log("initialising");
	
	bow_dbgLog("debug mode is enabled");
	bow_dbgLog("data directory at \"" bow_datDir "\"");
	bow_dbgLog("angle unit:             %.3f radians",0x1p0f);
	bow_dbgLog("distance unit:          %.3f metres",bow_distMod);
	bow_dbgLog("mass unit:              %.3f kilograms",bow_massMod);
	bow_dbgLog("time unit:              %.3f seconds",bow_tmMod);
	bow_dbgLog("gravitational constant: %f (factor: %f))",bow_gravConst,bow_gravConstFac);

	bow_gfxDat gfxdat;
	
	bow_initRnd();
	bow_initSig();
	bow_initGfx(&gfxdat);
	
	likely (opts.skip || !bow_intro(&gfxdat)) {
		if (!opts.hasSavPth) opts.savPth = bow_getSavPth();

		bow_plDat pldat;

		if (opts.newSav) bow_new(&pldat);
		else             bow_cont(&pldat,opts.savPth);

		bow_loop(&gfxdat,&pldat);

		bow_sav(opts.savPth,&pldat);

		if (!opts.hasSavPth) free((char *)opts.savPth);
	}

	bow_quit(&gfxdat,bow_stat_ok);
}

int main(int const argc,char const * const * argv) {
	bow_init(argc,argv);
}
