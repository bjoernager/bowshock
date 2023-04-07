// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.h>

#include <zap/mem.h>
#include <zap/str.h>

void bow_chkParams(bow_termOpts * const optsptr,int const argc,char const * const * argv) {
	char const * const progNm = *argv;

	bow_termOpts opts = {
		.hasSavPth = false,
		.newSav       = false,
		.skip      = false,
	};
	
	unlikely (argc >= 0x2) {
		char const * const * const stop = (argv++)+(zap_sz)argc;
		
		for (;argv != stop;++argv) {
			char const * param = *argv;
			
			if (param[0x0u] == '-' && param[0x1u] == '-') {
				param += 0x2u;
				     if (zap_streq(param,"credits")) bow_cred();
				else if (zap_streq(param,"help"))    bow_help(progNm);
				else if (zap_streq(param,"new"))     opts.newSav  = true;
				else if (zap_streq(param,"skip"))    opts.skip = true;
				else                                 bow_logErr("invalid parameter \"%s\"",param);
				continue;
			}
			
			// Else: Interpret it as a save path.
			opts.savPth    = param;
			opts.hasSavPth = true;
		}
	}
	
	zap_cp(optsptr,&opts,sizeof (opts));
}
