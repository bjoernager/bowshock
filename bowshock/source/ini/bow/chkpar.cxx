// Copyright 2022-2023 Gabriel Jensen.

#include <bow/ini.hxx>

#include <zp/mem>
#include <zp/str>

auto ::bow::bow::chkpar(::bow::trmopt & opt,int const argc,char const * const * argv) noexcept -> void {
	char const * const progNm = *argv;

	opt = ::bow::trmopt {
		.hassavpth = false,
		.newsav     = false,
		.skip      = false,
	};
	
	if (argc >= 0x2) [[unlikely]] {
		char const * const * const stop = (argv++)+(::zp::siz)argc;
		
		for (;argv != stop;++argv) {
			char const * par = *argv;
			
			if (par[0x0u] == '-' && par[0x1u] == '-') {
				par += 0x2u;

				     if (::zp::strequ(par,"credits")) crd();
				else if (::zp::strequ(par,"help"))    hlp(progNm);
				else if (::zp::strequ(par,"new"))     opt.newsav  = true;
				else if (::zp::strequ(par,"skip"))    opt.skip = true;
				else                                  bow_logerr("invalid pareter \"%s\"",par);

				continue;
			}
			
			// Else: Interpret it as a save path.
			opt.savPth    = par;
			opt.hassavpth = true;
		}
	}
}
