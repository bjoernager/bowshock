// Copyright 2022-2023 Gabriel Jensen.

#include <bow/gfx.h>
#include <bow/lgc.h>
#include <bow/sav.h>

#include <inttypes.h>
#include <stdlib.h>
#include <zap/str.h>

void bow_init(int const argc,char const * const * const argv) {
	bow_termopts opts;
	bow_chkparams(&opts,argc,argv);
	bow_rawlog("\x1B[0m\x1B[1mBowshock\x1B[0m %" PRIXLEAST64 ".%" PRIXLEAST64 ".%" PRIXLEAST64 " \u2013 Copyright 2022\u20102023 \x1B[1mGabriel Jensen\x1B[0m.\n\n",bow_vermaj,bow_vermin,bow_verpat);
	bow_log("initialising");
	bow_dbglog("debug mode is enabled");
	bow_dbglog("angle unit:    %f radians",0x1p0f);
	bow_dbglog("distance unit: %f metres",bow_distmod);
	bow_dbglog("mass unit:     %f kilograms",bow_massmod);
	bow_dbglog("time unit:     %f seconds",bow_tmmod);
	bow_gfxdat gfxdat;
	bow_initrnd();
	bow_initsig();
	bow_initgfx(&gfxdat);
	{
		zap_i8 const quotid = (zap_i8)bow_rnd() % 0x21u;
		char const * quot;
		char const * src;
		if (bow_getquot(&quot,&src,quotid)) {
			bow_logerr("invalid quote identifier (%" PRIXLEAST8 ")",quotid);
			bow_getquot(&quot,&src,0x0u);
		}
		bow_rawlog("\n%s\n\u2014 %s\n\n",quot,src);
	}
	if (opts.skip || !bow_intro(&gfxdat)) {
		if (!opts.hassavpth) opts.savpth = bow_getsavpth();
		bow_playdat playdat;
		if (opts.rstart) bow_rstart(&playdat);
		else             bow_cont(&playdat,opts.savpth);
		bow_loop(&gfxdat,&playdat);
		bow_sav(opts.savpth,&playdat);
		if (!opts.hassavpth) free((char *)opts.savpth);
	}
	bow_quit(&gfxdat,bow_stat_ok);
}

int main(int const argc,char const * const * argv) {
	bow_init(argc,argv);
}
