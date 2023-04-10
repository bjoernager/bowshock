// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.hxx>

#include <zap/mem.hh>
#include <zap/str.hh>

void ::bow::bow::chkParams(::bow::termOpts & opts,int const argc,char const * const * argv) noexcept {
	char const * const progNm = *argv;

	opts = ::bow::termOpts {
		.hasSavPth = false,
		.newSav     = false,
		.skip      = false,
	};
	
	if (argc >= 0x2) [[unlikely]] {
		char const * const * const stop = (argv++)+(::zap::sz)argc;
		
		for (;argv != stop;++argv) {
			char const * param = *argv;
			
			if (param[0x0u] == '-' && param[0x1u] == '-') {
				param += 0x2u;
				     if (::zap::streq(param,"credits")) cred();
				else if (::zap::streq(param,"help"))    help(progNm);
				else if (::zap::streq(param,"new"))     opts.newSav  = true;
				else if (::zap::streq(param,"skip"))    opts.skip = true;
				else                                    bow_logErr("invalid parameter \"%s\"",param);
				continue;
			}
			
			// Else: Interpret it as a save path.
			opts.savPth    = param;
			opts.hasSavPth = true;
		}
	}
}
