// Copyright 2022-2023 Gabriel Jensen.

#include <bow/bs.h>

#include <zap/mem.h>
#include <zap/str.h>

void bow_chkparams(bow_termopts * const optsptr,int const argc,char const * const * argv) {
	char const * const prognm = *argv;
	bow_termopts opts = {
		.hassavpth = false,
		.rstart     = false,
		.skip      = false,
	};
	if (argc >= 0x2) {
		char const * const * const stop = (argv++)+(zap_sz)argc;
		for (;argv != stop;++argv) {
			char const * param = *argv;
			if (param[0x0u] == '-' && param[0x1u] == '-') {
				param += 0x2u;
				     if (zap_streq(param,"help"))    bow_help(prognm);
				else if (zap_streq(param,"restart")) opts.rstart = true;
				else if (zap_streq(param,"skip"))    opts.skip  = true;
				else                                 bow_logerr("invalid parameter \"%s\"",param);
				continue;
			}
			// Else: Interpret it as a save path;
			opts.savpth    = param;
			opts.hassavpth = true;
		}
	}
	zap_cp(optsptr,&opts,sizeof (opts));
}
