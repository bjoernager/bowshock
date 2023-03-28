// Copyright 2022-2023 Gabriel Jensen.

#include <bow/gfx.h>
#include <bow/lgc.h>
#include <bow/sav.h>

#include <inttypes.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <zap/str.h>

[[noreturn]] void bow_init(int argc,char const * const * argv);

sig_atomic_t volatile bow_gotintr;

static void bow_intrhandl(int const sig) {
	signal(sig,bow_intrhandl); // Ignore the return value.
	bow_gotintr = 0x1;
}

void bow_init(int const argc,char const * const * argv) {
	char const * const prognm = *argv;
	char const * savpth;
	bool         hassavpth = false;
	bool         skipsavld = false;
	if (argc >= 0x2) {
		char const * const * const stop = (argv++)+(zap_sz)argc;
		for (;argv != stop;++argv) {
			char const * param = *argv;
			if (param[0x0u] == '-' && param[0x1u] == '-') {
				param += 0x2u;
				     if (zap_streq(param,"help"))  bow_help(prognm);
				else if (zap_streq(param,"reset")) skipsavld = true;
				else                               bow_logerr("invalid parameter \"%s\"",param);
				continue;
			}
			// Else: Interpret it as a save path;
			savpth    = param;
			hassavpth = true;
		}
	}
	srand((unsigned int)time(nullptr));
	{
		zap_i8 const quotid = (unsigned int)rand() % 0x21u;
		char const * quot;
		char const * src;
		if (bow_getquot(&quot,&src,quotid)) {
			bow_logerr("invalid quote identifier (%" PRIXLEAST8 ")",quotid);
			bow_getquot(&quot,&src,0x0u);
		}
		bow_rawlog("\n%s\n\u2014 %s\n\n",quot,src);
	}
	bow_rawlog("\x1B[0m\x1B[1mBowshock\x1B[0m %" PRIXLEAST64 ".%" PRIXLEAST64 ".%" PRIXLEAST64 " \u2013 Copyright 2022\u20102023 \x1B[1mGabriel Jensen\x1B[0m.\n\n",bow_vermaj,bow_vermin,bow_verpat);
	bow_log("initialising");
	bow_dbglog("debug mode is enabled");
	bow_gotintr = 0x0;
	if (signal(SIGINT,bow_intrhandl) == SIG_ERR) {
		bow_log("unable to set signal handler");
		bow_abrt();
	}
	if (!hassavpth) savpth = bow_getsavpth();
	bow_playdat playdat;
	bow_cont(savpth,&playdat,skipsavld);
	bow_gfxdat gfxdat;
	bow_initgfx(&gfxdat);
	bow_loop(&gfxdat,&playdat);
	bow_sav(savpth,&playdat);
	if (!hassavpth) free((char *)savpth);
	bow_quit(&gfxdat,bow_stat_ok);
}

int main(int const argc,char const * const * argv) {
	bow_init(argc,argv);
}
