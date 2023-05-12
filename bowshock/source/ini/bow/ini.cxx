// Copyright 2022-2023 Gabriel Jensen.

#include <bow/ini.hxx>
#include <bow/lgc.hxx>
#include <bow/run.hxx>
#include <bow/sav.hxx>

#include <cinttypes>

auto ::bow::bow::ini(int const argc,char const * const * const argv) noexcept -> void {
	::bow::trmopt opt;
	chkpar(opt,argc,argv);
	
	priquo();
	
	bow_lograw("\x1B[0m\x1B[1mBowshock\x1B[0m %" PRIX64 ".%" PRIX64 ".%" PRIX64 " \u2013 Copyright 2022\u20102023 \x1B[1mGabriel Jensen\x1B[0m.\n\n",::bow::vermaj,::bow::vermin,::bow::verpat);
	
	bow_log("initialising");
	
	bow_logdbg("debug mode is enabled");
	bow_logdbg("data directory at \"" bow_datdir "\"");
	bow_logdbg("angle unit:             %.3f radians",0x1p0f);
	bow_logdbg("distance unit:          %.3f metres",::bow::dstmod);
	bow_logdbg("mass unit:              %.3f kilograms",::bow::masmod);
	bow_logdbg("time unit:              %.3f seconds",::bow::timmod);
	bow_logdbg("gravitational constant: %f (factor: %f))",::bow::grvval,::bow::grvfac);

	inirnd();
	inisig();
	inigfx();
	
	if (opt.skp || !srtseq()) [[likely]] {
		if (!opt.hassavpth) {opt.savpth = getsavpth();}

		if (opt.newsav) {::bow::newsav(plydat);}
		else            {::bow::cnt(plydat,opt.savpth);}

		lop();

		::bow::sav(opt.savpth,plydat);

		if (!opt.hassavpth) {delete[] const_cast<char *>(opt.savpth);}
	}

	exi(::bow::cnd::oky);
}

int main(int const argc,char const * const * argv) {
	::bow::bow bow;
	bow.ini(argc,argv);
}
